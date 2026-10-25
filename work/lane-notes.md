
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
