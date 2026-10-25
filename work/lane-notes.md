
## Low-range window notes (0x80033000)

- **`lui` temp for an absolute global goes to a scratch register, not the destination**, when that
  destination is also the call argument the game reuses (`func_80034B98`, `func_8001D040`, both 2 words
  short). Declaring the symbol as a struct, an array, or a `u8[0x40]` all leave the same `$v0`/`$v1` choice.
- **A store as the last statement of a leaf function gets pulled into the `jr` slot** by gcc 2.8.1
  (`func_80033804`, `func_800337C4`); the game's build leaves the slot as `nop`. Both are one word short
  with an otherwise identical body.
- **The temp-register pool starts at `$v0` for us and at `$t0` for the game** on long straight-line
  copies (`func_80033E14` 24/25, `func_80033818` 12/13). Same instruction order, same count, different
  names — not reachable by reshaping the source.
- **A gp-relative base that reaches past 8 bytes** is spelled `extern u8 sym[8];` plus a cast
  (`func_800347FC` writes +0..+0xC). An `addiu $gp` base proves the declaration should stay small.
- **Data living just past a function's end** is addressed as `(u8 *) func_XXXXXXXX + N`, which reproduces
  the game's `%hi(func + 0x38)` relocation exactly (`func_800333C8` family); no data symbol needed.

## Low-band notes (0x80012000 / 0x80019000 / 0x80025000)

- **Early-return placement decides the branch sense.** `if (t == 0) return 0; return f(p, t);` produced the
  game's `beqz` + fall-through call; `if (t != 0) return f(...)` inverted it and cost a word
  (`func_80012078`).
- **A u16 store's scale must be its own statement** when the same index also feeds a word store:
  `j = i * 2;` keeps the `sllv` above the `sw`, inline `i * 2` sinks it and forces an extra reload of the
  index (`func_80025A0C`, `func_80025B10`).
- **`sll 16` / `sra 16` on a parameter before the first call is a `s16` declaration**, not a cast
  (`func_80012240`); but the reverse trap is real too — `func_800122A0` needed an `s32` parameter with an
  `s16` *return* to avoid the same extension.
- **Search loops over a stride table** want a `u8 *` walking pointer (`sltu` compare) and the bound computed
  as `count * stride`, not as an index (`func_80012024`).

## Windows 0x8001F000 / 0x8002B000 notes

- **Byte RMW reordering.** `p[0x38] -= 4; p[0x39] -= 4; p[0x3A] -= 4;` emits `38, 3A, 39`; writing the
  game's visible order (`38, 3A, 39`) in C produced `38, 39, 3A`. Trust the C order that *inverts* to the
  asm (`func_8001FD14`).
- **`for (i = 0, p = D; ...)` fixes prologue allocation** when two callee-saved registers are in play;
  separating the init into two statements swaps `$s0`/`$s1` (`func_8001FF5C`).
- **`lh` plus `sll 16` is a signed halfword shifted into the high half**, i.e. fixed-point 16.16 `(s16)v << 16`
  (`func_8002B870`), not a cast of the whole expression.
- **Absolute globals must be declared >8 bytes** or they come out `%gp_rel`; the `lui`+`lw %lo` pair is the
  signal (`func_8002BA54`, `func_8002B168`).

## Typed table slot for indirect calls
`((fn_tbl *) base)[idx].handler(...)` — declare the slot's type as a function pointer in a struct.
Untyped `*(void **) (base + idx * stride + 4)` indexing emits the extra `addu` and drops the call's
delay-slot `addu $a0, p, $zero` (`func_8002DD38`).

## Per-file cflags close two "allocation" classes (2026-10-25 retest)
Re-audit of 115 parked drafts with every allowed per-file cflag: 3 fell.
- `-mno-split-addresses` matches the `lui $a0; lw $a0, %lo` form where gcc otherwise takes a
  separate temp register (`lui $v0; lw $a0`) — `func_8001D040`, `func_80034B98`. The tell is a
  global load whose address temp and destination are the same register in the game.
- `-fno-schedule-insns` closes one pure scheduler body (`func_8003A4A0`, 54 words, 23 diffs -> MATCH).
- Surviving classes (111 of 114): register-role swaps that persist under every flag and declaration
  (8001CD7C, 80019C0C/80019EE4, 8001D340, 8002BCB0, 80012274, 80034BD8), delay-slot fills
  (80033804, 80055820), `lui` hoists (80056A3C), loop-strength rotations (8001FCB0, 8002BA64).
  Do not re-open these on a declaration hypothesis; it has now been tried in every direction.

## Repeated global deref: do not cache
`a[1] = *((s32 *) D_X + 1);` per statement keeps the game's reload; `s32 *p = (s32 *) D_X;`
folds them into one load and drops words (`func_80011F24`, 0x50 vs 0x60).

## Single-return variable for two-outcome bodies
`if (c) r = A; else r = B; return r;` — two `return` statements change the branch layout and
lose the `addiu v0,zero,-1` delay slot (`func_8002C454`).

## -mno-split-addresses on call args
The flag also fixes `lui $a0; lhu $a0` argument materialisation, not just struct bases
(`func_80032AF4`, `func_80032A9C`).

## 64-bit multiply bodies are toolchain-bound
Game: `mult; nop; nop; nop; mflo; mfhi; srl; sll; or`. Pinned maspsx emits `mult; mfhi; mflo; ...`
with no padding (size 0x20 vs 0x2c). No C shape can add those nops; do not retry `func_80032C28`
on source alone (`-fno-schedule-insns*` and `-mno-split-addresses` all stay 10/11).

## Six-load-then-add vector bodies
`func_80032FF4` needs all six words loaded before the three adds; `+=` per field interleaves
(12/13), struct copies blow up to 0x78. Stays parked.

## 64-bit multiply: source shape found, only the pad missing
The `mult` (not `multu`) form appears iff the product is a **signed** 64-bit multiply:
`unsigned long long p = (unsigned long long) ((long long) a * (long long) b); return p >> 16;`
reproduces `mult`, `mflo`, `mfhi`, the `srl`/`sll`/`or` split and the `srl` (not `sra`) remainder.
What is left is the game's 3-`nop` mult latency pad, which the pinned maspsx does not emit
(size 0x20 vs 0x2c). Ruled out: `-fno-schedule-insns`, `-fno-schedule-insns2`, `-mno-split-addresses`.
Filed as toolchain issue #76; do not spend another source pass on it.

## 16-30 band: allocator ties, not structure
22 opened, 4 converted. The parks are consistent: a `u16` struct load that wants `$a1`
(`func_8002BCB0`), a whole register set shifted by one (`func_80032CF4`), `$t`-only temporaries for a
six-value shuffle (`func_80033818`). The two shapes that still paid in this band were structural:
typed struct pointer + descending count loop (`func_8001DC98`) and the gw-relative bump pointer with a
separate `next` local (`func_8002DE18` needed the `addu a1,v0` copy, never reached).

## -O1 is a real lever for scheduler-parked bodies
The 15-cell flag matrix (census, 22 parked bodies) converted exactly one body and it was `-O1`:
`func_80056A3C` went 2/10 → MATCH with the source unchanged, a `lui` hoist the `-O2` scheduler had been
forcing. Try `-O1` before declaring a scheduling residue a wall; it is not only the #46 narrow-mask fix.

## Flag matrix verdict on the register-role class
`-mno-split-addresses`, `-fno-schedule-insns`, `-fno-schedule-insns2`, `-G0`, `-G4`,
`-fno-strength-reduce`, `-O3`, `-O1` and six pairs do **not** move `80033818` (12/13), `80032CF4`
(16/18), `8002BCB0` (2/17), `8001D804` (11/23), `800132FC`, `80032FF4`, `80032D88`, `80011B48`.
Only `-fno-schedule-insns2` on `8002DE18` (17→7) and `-G0` on `800122A0` (10→8) change anything, and
neither reaches the body's remaining structural gap. The register-role class is source-shape or nothing;
stop spending flags on it.

## Optimization level: what the repo permits and what it means
Permitted per-file `-O` levels are `-O0`, `-O1`, `-O2`, `-O3` (not `-Os`: `scan.py` rejects it with
"cflag -Os is not in toolchain/compiler.toml allowed_cflags"). A unit that needs a level carries it on
line 1 as `/* cflags: -O1 */`; scan/gate/build accept it end-to-end (`func_80056A3C` is the shipped
example). Interpret a level-carrying unit as: the body's segmentation matched the `-O2` compiler except
for a known scheduler/code-motion decision, and `-O1` reproduced it. Say which decision in the census row.
Measured over 164 parked bodies: `-O3` ≡ default (all 164 identical), `-O0` destroys the body (162 worse),
`-O1` helps 26 and hurts 103. Only `-O1` is a live lever, and only for `lui`-hoist / loop-invariant-move
residues.

## Prune the draft when the unit ships
A near-miss draft for a merged unit is worse than no draft: the level sweep re-reported four of them as
conversions. Pruning is part of shipping a unit — when a unit lands, move its drafts to
`work/near-miss/archive/` (the sweep globs `work/near-miss/*.c`, so a subdirectory is invisible to it).
59 stale drafts were archived this pass.

## `volatile` for a store swallowed into the `jr $ra` delay slot
Signature: the game ends `sw; jr $ra; nop`, our build gives `sw; jr $ra; sw` (size one word short). gcc's
delay-slot filler sinks the last store into the return slot; marking the destination `volatile` blocks the
move and restores the `nop`. `func_80032FE0` and `func_80033804` both match this way (3/5 → MATCH). The
stores are unconditional, so `volatile` is a scheduling barrier, not a behaviour change. Use it only for
this signature: on a body where the store already matches, `volatile` will wreck the allocation.

## Delay-slot store barrier: scope, and why it is not a family
The `volatile` barrier converts only bodies whose residue is *the last store swallowed into the `jr $ra`
slot*: game `sw; jr $ra; nop`, ours `sw; jr $ra; sw`, size one word short, both diffs in the last two
words. Measured corpus-wide (268 drafts, default and `-O1`): exactly two bodies qualify, both shipped in
#81. A store or load word sitting in a *branch* slot is a different residue and no barrier touches it.
Do not apply `volatile` to a body whose stores already match — `80026E88` went 12/16 → 17/16 and
`80015D38` 2/20 → 3/20 that way. Probe first, then barrier.

## Three shapes proved on the sub-20-word tail this pass
- **Guarded bottom-tested copy loop**: `i = n - 1; if (n != 0) { do { *dst++ = *src++; } while (--i != -1); }`
  reproduces `beqz n; addiu i,n,-1; addiu a2,-1;` then `lbu/addiu/addiu/sb/bne/addiu`. The equivalent
  `for` form duplicates the guard and is one word long.
- **Folded `&&` chain, positive test**: `if (a==0 && b==0 && c==0) return 1; return 0;` gives the game's
  `beqz`+`addiu $v0,1` delay-slot form; the negative cascade `if (a) return 0; …` collapses the tail to
  `sltiu`.
- **Split the reassociable arithmetic into two statements**: `a - (m - 4)` is rewritten by gcc to
  `(a + 4) - m` (4/15); `t = m - 4; result = a - t;` stops the reassociation and matches.

## The unopened-body queue starts at 20 instructions
`work/enum_fresh.py` (no draft, no census mention, no handwritten/GTE) finds 290 bodies, smallest **20**.
The sub-16 and 16-19 bands are now empty of unopened bodies, so the tail ends here; every future pass
should start at the 20-word floor and re-run that script because it excludes anything this file mentions.

## Two shapes that paid at 20-26 words
- **Statement order beats initialisers**: in `func_8002B57C` the store `self->f3C = 0` must come before
  `n = h->head`. Writing `N *n = h->head;` and storing afterwards lets gcc hoist the load above the store
  and shifts every following word — 24/24 diffs from a one-line difference.
- **Do not let gcc see the third argument twice**: `func_8002E848` needs `f(buf, (s16) c, c)` with the
  parameter declared `s32`. Declaring it `s16` and passing it twice makes gcc materialise a copy (`addu`)
  and the call no longer matches.

## The register-role class survived four role-forcing shapes per body
For `8001F4E8` (2/26), `8001DB74` (2/26), `8002FE80` (2/24) and `8002050C` (4/25) the instruction sequence
and every branch target already match; only the register holding one value differs. Shapes tried per body:
a separate local per value, a typed array index, a base-pointer local, a wider parameter with a cast on use,
a round-trip through a third local, and an incremented field (`self[0xB] += 4`). None move the role; several
make it worse. Treat this class as **unreachable from source** until the allocator itself is understood —
budget one draft, record the residue, move on.

## The 29-35 word band converts on structure alone
Eight of eleven drafts matched, most on the first attempt, with no flag, level or barrier tricks:
frame size and struct strides first (0x6C entry stride in `8001DBDC`, 0x94/0x40 list links in `8002B708`,
0x24 slot stride in `8002B194`), then the field width (`u16` flags, `s32` beside them), then statement order.
Two recurring word-level tells: an asymmetric compare written the wrong way round is exactly one word
(`key == (*(u16 *)(e + 2) & 0x1F)`), and a missing saved register shows up as a frame 8 bytes too small.

## The 64-bit fixed-point class is a compiler limit, not a source shape
`800331FC`, `8003302C` and `8003353C` all want `(s32)(((long long) x * y) >> 16)` emitted as
`mult; mflo; mfhi; srl 16; sll 16; or`. gcc 2.8.1-psx expands the 64-bit shift into a full shift sequence
(35/27, 34/29, 37/30 and larger). Do not spend shapes on this class until the shift is expressible another
way; record and park.

## The 33-40 word band: indexed off the base, not through a walker
Eleven of sixteen drafts matched. The one shape that decided several of them: when the game's loop pointer
equals the function's own base pointer (as in `func_80013FD0`, `v1 = a0` with fields at +0x17C), writing a
`u8 *p = arg0` walker makes gcc fold the base into `p` (`addiu $v1, $a0, 0x1A0` / `lw -0xC($v1)`) and every
offset in the body shifts. Index straight off the parameter instead and the game's `0x17C($v1)` comes back.
The same folding costs a body its base symbol: `D_800A4F00 + 4` becomes a `lui` of `D_800A4F04`, while
`((s32 *) D_800A4F00)[1]` keeps the `lui`/`lw 0x4` pair. Declaring the global as a typed array and indexing it
is what holds the symbol still.

Two smaller tells from the band: a loop whose counter is also a value the game keeps in the loaded register
wants `do { } while (i != -1)` (a `for` with a pre-test adds the guard word), and duplicated straight-line
code in both arms of an `if` only stays duplicated when the arms differ by more than a constant — moving the
shared base assignment into each arm is what reproduced `func_80033F78`'s two loops.

## `-O1` reaches the 64-bit `>> 16` sequence; it does not close it
`800331FC` under `/* cflags: -O1 */` with explicit locals emits exactly `mult; mflo; mfhi; srl 16; sll 16; or`
per element — the shape the class was parked on. It is one word over (0x70 against 0x6c): gcc materialises the
high half of the 64-bit shift result as a dead `srl` that `-O1` does not delete, and `-O2` replaces that with a
stack spill of the DImode pair. Read a 64-bit body's `-O1` result as "sequence correct, one word per multiply
too long" rather than as a source problem; `8003302C` and `8003353C` behave the same way (34/29 and 33/30).
Do not spend shapes on this class without a way to make the truncated DImode result visible to the optimiser.

## The 41-55 band is allocation-bound, not shape-bound
Sixteen first drafts produced four units (25%), against 69% in the 33-40 band. The failures are not missing
structure: `func_8002D904` is 7 of 46 words with the whole instruction stream correct, and `func_80034758` is
11 of 41 with the size already exact. Past ~40 words the allocator has enough live values that a swapped
callee-saved pair or one value in `$a0` instead of `$a3` is the normal outcome, and no declaration order,
scope or pointer form tested moved it. Budget one or two shapes at this size, record the diff and move on;
the band does not reward depth.

Two things still pay at this size, both structural rather than cosmetic: a masked flag means a **narrow**
variable (`u8 flag` produced `andi 0xFF` before the branch in `func_80018C64`), and a callee that takes the
walked pointer as its argument is what forces `addu $a0,$s0,$zero` into the branch delay slot. Both are the
same lesson as the 33-40 band: read the masking and the argument setup off the assembly before writing types.

## A filled load-delay nop looks like a missing word, not a missing instruction
`func_80022308`/`800223AC` sit 3-4 words short with the address arithmetic and all nine copy pairs already
correct. The absent words are `nop`s: the original leaves the load-delay slot after `lw 0xFF8($a0)` empty, and
our build fills it with the `addiu` of the tag constant it is about to store. That is the scheduler choosing a
legal file, not a source shape — the same code with the constant materialised later (`addiu` immediately
before the `sw`) is what the game has, and the C that produces it is `e->f[0] = 7` with the constant written
inline. Treat a 3-4 word deficit on an otherwise word-perfect body as this class before re-reading the source.

## A re-measure is cheaper than a re-think: `work/retest.py`
Re-running every draft in `work/near-miss/` (313 files, one line each) against current `main` takes one
command and gives the pass its cheapest-first ordering *measured*, not remembered. Three of the bodies the
census listed as 4-8 words off now measure 2, and one (`func_80012274`) converted on a single type change.
Do this first on any pass that intends to retest: previous verdicts are a stale cache.

## A narrow **parameter** is its own shape
`func_80012274` needed `s16 v` in the signature, not an `s32` local holding the value: with the parameter
narrow, gcc copies it to a fresh pseudo (`addu $v1,$a0,$zero` in the `beqz` delay slot) and negates that
copy in place; with `s32` it coalesces the local with the parameter and negates `$a0` directly. So the
narrow-variable tell from the 41-55 band extends to **parameter types**: when the assembly has a copy of an
argument into a second register on one path and an in-place computation of the argument on the other, read
the parameter as the narrow type.

## What a `lui` address temp is *not*
`-mno-split-addresses` fixes a `lui` temp only when the game materialises a *whole* address up front. On a
body where the game has `lui $a0` / `lw %lo($a0)` into an argument register (`func_8003BF7C`,
`func_80056C90`, `func_8003B8F8`) the flag costs 29 of 36 words and 78 of 79 — every address in the body
becomes absolute. Check whether the mismatch is the *temp register* (allocation: leave it) or the *split
itself* (flag: use it) before spending a variant on it.

## Loads into argument registers are the role class, one level up
The retest found the role class in a new dress: the game loads a value straight into `$a0`/`$a1` (about to be
a call argument, or the argument itself) while our build loads it into `$v0` and copies. Nine bodies park on
exactly that, and no spelling tested — inlining the argument, comma-declaring the locals, taking the address
of a local, passing an oversized extern through `*(u32 *)` — moves a load out of `$v0`. Treat "the game's
load target is an argument or callee-saved register and ours is `$v0`" as the closed role class and budget
one draft.

## Subscript, not walker, when a body *indexes* a table
`func_8001CD7C` (2 of 10, parked for four passes) matched the moment the base became a typed table pointer
and the store used a subscript: `E *tab = (E *) base; tab[i].f0 = b; tab[i].f4 = a;` gives the game's
`lw $a2,base` / `sll $v1,$v0,3` split. Every walker spelling — `u8 *e = base + i * 8`, `(E *) base + i`,
a `base` local, a `s16`/`u16` index — keeps `$a2` and `$v1` swapped, which is why the body read as an
unfixable saved-pair swap. The 33-40 band's rule ("index off the parameter, not through a walker") is the
same finding from the other side: a body that *walks* wants a walker, a body that *indexes* wants a
subscript, and the register split follows the form.

## The parked corpus' cheap tail is allocation, measured body by body
Six bodies at six words or fewer were each given the shapes that have been converting, and none moved
below its residue (the seventh, `func_8001CD7C`, converted on the subscript form above): `80042E9C` halved from 4 to 2 of 58 on a real fix worth keeping (a callee declared `s32`
and called in `return` position, not as a statement followed by `return 0x27100000` — the constant has to be
live across the `if`, which is what puts `lui $v0,0x2710` in the `beqz` delay slot), but the last two words
are a load into `$v0` that the game keeps in `$a1`. Treat "N of M with N ≤ 6" on a parked body as this class
and budget one draft: the cheap list is finished.

Two reusable tells from the pass:
- **A return constant in a branch delay slot means the value is live across the branch.** If `lui $v0,0xNNNN`
  sits in a `beqz`/`bnez` slot and the epilogue does not reload it, the source computed the return value
  *before* the `if` — usually because the `if` body is `return f(...)`, so the other path's constant has to
  survive the call. Writing the `if` body as a statement plus a trailing `return` puts the constant at the
  end instead and costs 2 words.
- **`lui $vN` twice up front beats an assignment order.** `func_8003BDB8` materialises two constants before
  four stores; gcc sinks the second to its single use no matter which assignment comes first, so a body whose
  only difference is a constant's position is not a statement-order problem.

## The argument-register axis is closed with two forms
For bodies where the game loads into `$a0`/`$a1` and our build uses `$v0`, both the inline-argument form and
the "load feeds the first parameter of the next call" form were tried on `func_8003B8F8` (4/46 both) and
`func_80042E9C` (2/58 both). Neither moves the destination register. The game's `lui $a0` / `lw $a0` is the
whole-address-materialisation shape, which `-mno-split-addresses` reproduces only at the cost of every other
address in the body (measured 78/79 and 31/36). Record the class and move on.

## Fresh-ground tells from the 41+ queue
- **A wide parameter leaves no mask.** `func_80014170`'s third argument tests `beqz $a2` with no `andi`; a `u8`
  parameter emits `andi $v0,$a2,0xFF` first and shifts every following word. When the assembly branches on a
  parameter with no mask, declare it `s32`/`u32` even if the callers only pass 0/1.
- **A small symbol can still be an array base.** `extern u8 D_8008AD14[4];` plus
  `(Rec *) (D_8008AD14 + n * 0x14)` keeps `addiu $a2,$gp,%gp_rel(D_8008AD14)` and the game's `sll 2 /
  addu / sll 2` index scale. The same symbol declared as `extern Rec D_8008AD14[]` is >8 bytes, so gcc
  switches to `lui`/`addiu` and the whole body shifts.
- **Declaration order writes the prologue.** In `func_80034698` the first three definitions must be
  `char *p = dst; u32 value = v; u16 n = 0;` to get `t0 = a0`, `v1 = a1`, `a1 = 0` in that order; declaring
  the loop-variable copy first gives `v1 = a1` first and swaps `$a1`/`$t0` through the whole body.
- **gcc biases a walker when every access is positive.** `func_800257A0` walks `e += 0x8C` but every field is
  at a positive offset, so our build sets the walker to element+0x74 and uses negative offsets; the game keeps
  the element base. The bias is identical for `u8 *` and struct-pointer spellings, so this is a compiler
  decision, not a source shape.

## Families, not bodies: `work/cluster.py`
Two keys, both computed from the listing with the address-dependent parts normalised away (displacements to
`<off>`, `%hi`/`%lo`/`%gp_rel` symbols and branch targets to `<sym>`/`<tgt>`, registers to `$Aa..$Zz` in
first-appearance order):
- **shape** — the normalised instruction stream, clustered by greedy leader similarity (difflib ratio >= 0.90;
  a size-band + opcode-multiset prefilter keeps it to a second over 1081 bodies). This finds exact twins only:
  310 unopened bodies hold 309 distinct shapes and one twin pair. Useful for *confirming* a family, useless for
  finding one.
- **callee set** — the frozenset of `jal` targets. Bodies with no calls must be excluded or every leaf body in
  the binary joins one family. This is the key that works: 543 families, 56 unopened bodies whose family already
  contains a matched member, and the members differ in length (0xE0 to 0x4D4 in the `80015E8C`/`15F10` family).

**The rule: reach for the callee set first, then read the matched sibling's C before drafting.** The transferable
part is the idiom, not the text — which of the `arg` fields are `s32 *` and which `u8 *`, whether the callee takes
out-parameters (`func_80020C34`'s `v[3]`) or returns a pointer, whether stores go straight to the destination or
through a local triple, and which arm gcc put first. Four of seven drafts matched that way, several in one shape.

Two tells that came out of it:
- **Push the zero store last.** `func_8001F468` matches only with `f24 = a1[0]; f2C = a1[1]; f28 = 0;` — with the
  zero store before the second load, gcc hoists it into the first load-delay slot and the body ends up a word
  short with no `nop` at `+0x14`. A missing load-delay `nop` right after an argument load means the *next*
  statement in the source depends on that load; move the independent store down.
- **Branch polarity is a source-order decision, not a compiler one.** `func_80026FBC` flipped our `beqz` to the
  game's `bnez` purely by writing the arms as `if (s >= 7)`; the same trick converted earlier bodies. Write the
  arm the game jumps *to* as the `if` body.

## What a twin's identical divergence means
`func_8002D734` and `func_8002D81C` are the same function with X and Z swapped, and both park at 32 of 58 words
with the same residue (the `func_80035E40` return kept in `$v0` where the game copies it to `$a0`). When two
bodies that differ only in constants diverge identically, the residue is the allocator and no shape will fix it;
park both with one note rather than treating the second as a fresh body.

## Three bodies in this binary are not C
- `func_800262E8` / `func_80027538` — scratchpad stack switch (`lui 0x1F8003FC` / `sw $sp,0x10($t0)` /
  `addiu $t0,-4` / `addu $sp,$t0`); an asm macro in the original source.
- `func_80045828` — `lui $gp` / `lw $gp,-0x4C68($gp)` / `jr $ra`; a gp-reload stub, the only body that writes
  `$gp`. Detect all three by shape: a body that writes `$sp` other than in the prologue/epilogue, or writes
  `$gp` at all, is not transcribable and should be dropped on sight like a GTE body.

## The family key is spent — it needs siblings, not a template
`work/family_queue.py` reports 9 families with a matched template and **one** unopened member each, and 0 of the
6 drafted this pass matched. The four units the key produced earlier all came from families with 2-4 unopened
members. Rule: run the family key only where the cluster has **two or more unopened members**; a one-member
family costs the full template read to buy a single draft and lands in the same allocation wall as any other
100+ word body.

## Two delay-slot classes, in opposite directions
- **Missing (toolchain).** `func_8002DAE8` is 19 words short and every missing word is the two `nop`s the game
  leaves after each `mult` (seven of them). This is the same class as the `func_80032C28` report on the toolchain
  issue: it applies to plain `s16 * s16` products, not only to 64-bit fixed point. Read any body with `mult` as
  "sequence right, two words per multiply missing" and do not spend source shapes on it.
- **Extra (scheduler).** `func_80025544` is **+18**: one load-delay `nop` per statement, because our gcc cannot
  hoist the next `%gp_rel` load above the store through the parameter, while the game's build does hoist it.
  Grouping the loads, computing addresses into locals first, and `-O1`/`-O2`/`-O3` all fail to change it. So the
  census class is **delay-slot fill direction**, not "a missing nop".

## gcc folds a walked member pointer to its lowest offset
In `func_80052380`, a `u8 *p = e` (or a struct pointer, or an `s32 *` with `p[0x13]`) used only at +0x48/+0x4C/+0x50
is rewritten as `p = e + 0x48` with offsets 4/8/0, and the extra `addu` the game has (`s0 = s2`) disappears. The
game keeps both pointers live, which needs a use of `p` at an offset below the fold base. Worth one shape only:
if the fold survives, the body is a pointer-shape question the pass could not answer, not a statement-order one.

## Argument-register birth: spell a constant scale as a multiply
A value that the game computes in `$a0` and then copies to a callee-saved register in the `jal` delay slot is
**born as the call argument**. gcc picks that shape when the scale in the expression is a multiplication:

    size = *(u32 *) dst * 16;     /* MATCH */         size = *(u32 *) dst << 4;   /* homed in $s2 */

Fourteen source shapes and eight per-file flags fail to move the `<< 4` version off 3/87; the multiply is the
whole difference (`func_80020398`). What does *not* work: the same trick on a variable shift (`i * (1 << j)` in
`func_80026EC8` changes nothing), and bodies whose residue is a pointer fold or a global-address home rather than
argument birth. So read the tell first — argument register plus a pre-call copy — and only then reach for the
multiply spelling.
