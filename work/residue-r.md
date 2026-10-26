# Residues — pass `freebuff2/cluster-r`

Two units closed on this branch (`func_8001434C`, `func_80015604`, `func_8001ADEC`). Two parked,
one per window. Nothing half-matched is left in the tree.

## func_8001A108 (0xE4, claim #32) — 34 of 57 words, size exact (0xE4)

Everything up to and including the three `func_80032C28` calls matches. What is left:

1. **Dispatch shape.** Retail is a linear `beq` chain in the order **1, 0, 2** with every case
   jumping to one shared call block:

   ```
   beq  $s2,$v0,+9      ; case 1
   beqz $s2,+5          ; case 0
   beq  $s2,$v0,+6      ; case 2
   j    done
   case0: j call ; addiu $a0,2   (in the delay slot)
   case1: addiu $a0,3
   call:  ori $a1,0xFFFF ...
   ```

   `switch (arg0)` with cases 0/1/2 — in every spelling tried — is turned into the **binary tree**
   `beq 1` / `slti $s2,2` / `beq 2` (0xF0, three words long). The if-chain
   `if (a==1) n=3; else if (a==0) n=2; else if (a==2) n=4; else goto done;` gets the right order and
   the exact size but emits the inverted form `bne -> skip / j body` and lays the call block out
   directly after case 2's body, so cases 0/1 jump backwards into it.
2. **Allocno mirror.** Retail keeps the slot pointer in `$s1` and the allocator result in `$s0`
   (`sw $s0,0($s1)`); we get the opposite. Declaration order (p before slot, slot before p),
   assigning the slot after the call, and `s32` slot all leave it unchanged.

Permuter: 352+ iterations, best score 675 → 25 words, but 0xD4 (four words short) because it
inlines `4` into the call and deletes case 2's body. Not a path to MATCH.

## func_8001A710 (0x124, claim #32) — 53 of 73 words

The loop shape is right (`while (--n != -1)` rotates exactly like retail, `list += 0x18` in the
`bne` delay slot, the `-1` invariant in a register). What is left is the three distance terms:

Retail stores each `|x|>>16` once into `sp+0x10` / `sp+0x14` / `sp+0x18` **and** multiplies the
in-register value (`sw $v0,0x10($sp)` immediately followed by `mult $v0,$v0`), i.e. the three
locals are address-taken and assigned exactly once each. Writing them as `s32 d[3]` with
`d[k] = ...; d[k] >>= 16; if (d[k] < 0) d[k] = -d[k];` gives three stores per element (0x134).
Writing a scalar temp and assigning `d[k] = t;` once gives one store per element but gcc then
**reloads** from the slot for the multiply (0x134 → 0x130). Retail reloads neither and stores
neither twice; the shape that produces "store once, use the register" has not been found.
Secondary: retail keeps the cursor in `$a3` and the entry in `$a1`; we get `$a1`/`$a0`.

Not attempted further: permuter (the two shapes above both compile, and the gap is allocation,
not source text).

## Lever found this pass (not yet used by a shipped unit)

**A `while` loop is inverted by this gcc; a `goto` loop is not.** For the shared
`while (*(u32 *)(p + 8) < len) { p = *(u8 **)(p + 4); if (!p) return 0; }` walk in the
`0x80015xxx` region, every `while`/`for (;;)`/`do` spelling compiles to the rotated form
(preheader `j` to a bottom test, back edge to the body, one word shorter). Writing it as

```c
loop:
    if (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == NULL) {
            return 0;
        }
        goto loop;
    }
    return func_80015760();
```

keeps the test at the top with the back edge to it, which is what retail has. Checked on a
standalone probe with the pinned flags; `-O1`/`-O3`/`-fno-strength-reduce`/`-fno-schedule-insns2`
all still invert, so this is source shape, not flags. Cost of the `goto` form: gcc then
cross-jumps the `return 0` tails into one block, which is the next thing to defeat.

Also recorded here because it cost time: `func_80015684` (7/44) and `func_800159D8` (19/47) in the
`0x80015000` lane segment were both reverted, nothing staged.

## Toolchain gotcha that cost a whole pass (read this before calling a merged unit broken)

`toolchain/maspsx` is a **submodule** and `tools/cc.py` runs `toolchain/maspsx/maspsx.py` **from the
checkout**, not from the image's `.venv`. `toolchain/setup.py` applies
`toolchain/patches/maspsx/*.patch` into that submodule; a checkout that was set up before #38 has an
**unpatched** maspsx and silently skips the load-delay `nop` after a gp-relative `lw` that is
immediately followed by a use of the loaded register. Symptom: every "load a global, store it to
another global" unit is exactly one word short (`0x18` vs `0x1c`), and the diff is a single missing
`nop`.

`func_8003ED04` and `func_8004C2C8` were reported as broken in `main` because of this. They were not.
Fix and guard:

```sh
git -C toolchain/maspsx apply ../../toolchain/patches/maspsx/0001-extern-sdata-symbols-use-gp.patch
python3 toolchain/setup.py --check     # exits non-zero if any maspsx patch is unapplied
```

After patching, ninja will not rebuild the affected objects (maspsx.py is not a recorded dependency):
`rm -f build/src/funcs/<unit>.c.o` (note the `.c.o` suffix) before `tools/build.py`.

## Pass "window-30" (PR #73): 3 closed, 2 parked

Closed: `func_80014228` (immediate, once maspsx was patched), `func_80014C60` (matched
only after deleting the local `p0`/`p1`/`p2` cursor copies — with copies the output
pointer landed in `$s4` and the input in `$s6`; using the parameters directly puts
`$s4`/`$s5`/`$s6` in argument order and gcc creates the `+4` cursors itself),
`func_80014DA8` (first try, same family).

### func_80014170 (0xB8) — parked at 32/46, one word short

Everything except the magic-tag branch matches. Retail:

```
addu  $v0, $a0, $zero     ; save p
addiu $a0, $a0, 0x10      ; p += 0x10
addiu $v0, $v0, 0x10      ; saved + 0x10
j     .L80014204
sw    $v0, 0x0($a2)       ; slot[0] = saved + 0x10
```

So the source computes `p + 0x10` **twice** from a copy of `p` taken before the bump.
Ruled out (each folds the two adds into one, costing exactly one word):

- `slot[0] = p + 0x10; p = p + 0x10;`
- `q = p; p = p + 0x10; slot[0] = q + 0x10;` (gcc copy-propagates `q` away because
  it is dead after the store — the copy must stay live *past* the bump, as it does in
  the tail of this same function where `q` is read after `p += 4`)
- the same two through a `u32` temp / `(u32)q + 0x10`
- bump-then-store and store-then-bump orders
- two separate `if` statements instead of `else if`

The tail of the function (below `.L80014204`) *does* produce the copy-plus-two-adds
shape from `q = p; p = p + 4; slot[0xC] = p; slot[0x10] = *(u16 *)(q + 2);` — so the
magic branch needs a read of the pre-bump pointer that survives the bump.

### func_8001446C (0x2F0) — parked at 177/188, 0x2c0 vs 0x2f0

Coefficient chains exact: `k * 152` compiles to the `(k*5<<2 - k)<<3` chain and
`k * 228` to `(8k - k)<<3 + k <<2`, both as written. `D_8006E5D4` is reached with
`lui`/`addiu` (absolute), not `%gp_rel`.

Remaining: allocno order. Retail loads `*(s32 *)(arg0 + 8)` first, then the 5th
argument, then `base = *(u8 **)(arg0 + 0x38)` — and `base` lives in `$s1`, `D_8006E66C`
in `$s7`, the 5th argument in `$s6`, `arg2`/`arg3` in `$s4`/`$s5`. The current spelling
hoists `&D_8006E5D4` to the top of the prologue and puts `base` in `$s4`; reordering the
two loads did not change it.

### func_8001483C (0x2AC) / func_80014EE8 (0x71C)

Not attempted this pass.

### func_80014170 — permuter exhausted too

Two bounded runs (1 083 and 1 213 iterations, `-j6`, `timeout = 25` in
`work/permute/func_80014170/settings.toml`) never went below score 175. The best it found
(score 75) was `slot[0] = (u32)(p + 0x10)` **after** the bump — that reproduces the
`addu $v0,$a0,$zero` copy retail has, but stores `p_old + 0x20` instead of
`p_old + 0x10`, i.e. it is only a shape win and is *not* semantically equivalent, so it
cannot be shipped. Log: `work/permute-14170b.log`.

What the score-75 result proves: this gcc emits the copy-plus-two-adds shape when two
adders off the same base register need it — so the shape is reachable, and the missing
ingredient is a use of the pre-bump pointer that survives the bump *and* is not equal to
`p_new`.

### func_8001483C (0x2AC) — 78 of 171 words already exact

The whole prologue, the `neg[]` construction (including retail's *double* store per
element: `neg[i] = arg2[i]; ... neg[i] = -neg[i];` produces exactly the `sw` then
`negu`/`sw` pairs) and the entire `dot`/abs/`slti 0x28F` decision tree including the
cross-jumped `func_800330A4(b)` shared tail are byte-exact from `0x8001483C` to
`0x80014968`.

First divergence, `0x8001496C`:

```
game : jal func_800337C4      yours: addiu $s0, $sp, 0x50
game : addiu $a0, $sp, 0x50   yours: jal func_800337C4
game : lh  $v0, D_80089F50    yours: addu $a0, $s0, $zero
```

Retail materialises `&m1` (`$sp+0x50`) inline at every use; gcc caches it in `$s0`
instead, which adds exactly one word (0x2b0 vs 0x2ac) and cascades through the rest of
the function. Retail's `$s0` is used only for `&m2` (`$sp+0x80`), and only for the two
consecutive calls `func_800337C4(m2)` / `func_80033DB0(m2, arg1)`.

Two further details already known to be right but currently mis-scheduled: the angle load
must be `lh` for the `D_80089F50 != 0` test and a *separate* `lhu` for the value (both
appear in the draft), and the select is `ang = (D_80089F54 != 0) ? v : -v` with the copy
in the `bnez` delay slot.

Everything else about the draft is derived and worth keeping: `func_8003353C` returns
`s32` (a `void` prototype does not even compile), `D_80089F50` is `s16`, the four
vectors are 16 bytes apart (`s32 v[4]`), and the two matrices are 48 bytes at `$sp+0x50`
and `$sp+0x80`.

## Window #32 sweep (func_8001B980 MATCH; three units parked with word-level residue)

`func_8001B980` — **MATCH** (99 words). The levers that produced it:

* the three `func_8002C3C0` results must live in a `s32 t[3]` array: gcc 2.96 has no SRA,
  so an array stays in memory and reproduces retail's `sw $v0,0x10($sp)` /
  `lw $a0,0x10($sp)` round-trip. Registers gave seven extra callee saves.
* split `key` into two statements —
  `key = (*(u32 *)arg0 >> 8); key = key & 0x1F;` — which yields `srl $s1` + `andi $s1`
  and, as a side effect, the `nop` in the load-delay slot after `lhu $v0,D_8008AE16`.
  The one-statement spelling folds to `srl $v0` / `andi $s1,$v0` and is one word short.
* the descriptor block leaves 8 bytes of frame unused, so the unit needs a `u8 pad[8];`
  tail local (precedent: func_8001AF0C, func_80016204, func_8001BB1C). Without it the
  frame is 0x50 instead of 0x58 and every saved-register offset is wrong.
* `*(u32 *)(slot + 0x10)` is re-read at each of the three `func_80032C28` calls; hoisting
  it into a local makes gcc keep it in `$s0` and costs a word.

`func_8001A550` (106 words) — 11 words differ, all in the loop preheader. Draft:
`work/residue-a550.c`. Retail: `lw $v0,D_8008ADCC` / `addu $a0,zero,zero` /
`addu $s2,$a0,zero` / `blez $v0` / `lw $a2,0($s1)` / `addu $a1,$v0` /
`lui+addiu $v1,&D_80092654`. The `blez` is the `for` loop's entry test folded at `i == 0`,
while `&D_80092654` is materialised *after* the branch. Dropping the standalone `i = 0`
before the loop gives `blez` but moves the base address above the bound load and loses
`move $s2,$a0`; keeping it does the reverse. Everything from the loop body on is exact in
the `i = 0` spelling (t-array spill, key split, slot scan, descriptor build, the three
`func_80032C28` calls with the reloaded `slot+0x10`, `func_800122CC(a->f0, sp)`).

`func_8001A834` (106 words) — 70 words differ, allocno order. Draft: `work/residue-a834.c`.
Both `s16` count-down scans and the dispatch to `func_8001C2B8` are correct. Retail keeps
arg0 in `$s3`, the limit in `$s4`, the scan base in `$s5`, and *reloads* `p[2]` for the
`n = p[2]` store (`lbu $v0,2($s5)` / `sltu` / `lbu $s4,2($s5)`). The draft reuses one load.
Also learned: `n = 0xC` must be assigned *after* the `func_8001D198` call; assigning it
first folds the compare to `sltiu v0,v0,12` and hoists the `li` into the prologue.

`func_8001B684` (55 words) — 17 words differ and every one of them is a `$s0`/`$s1`
rename. Draft: `work/residue-b684.c`. Retail holds the entry pointer in `$s0` and the loop
index in `$s1`; gcc gives the index `$s0`. Declaration order, `register`, an extra `k`
temp and pointer initialisers all leave it unchanged. The switch is confirmed: jump table
`jtbl_800101E4` is `{tail, tail, func_8001B980, func_8001B760-block, func_8001B760-block}`
for `k = (*(u8 *)p) >> 4`, i.e. `case 0: case 1: break; case 2: func_8001B980(p,i);
case 3: case 4: if (((*(u32 *)p >> 13) & 0xF) == 0) func_8001B760(p,i);`.

`func_8001B504` was already matched on main (#79); the draft here was a regression and was
reverted — do not re-open it.

Not attempted this pass: `func_8001A9DC` (260 words), `func_8001B238` (90 words),
`func_8001B760` (136 words).

## Pass 2 (window #32, after PR #84 merged)

**`func_8001B684` closed — MATCH, shipped.** The `$s0`/`$s1` swap above is fixed by *naming
the `u16` argument*: `id = (u16)(D_8008AE14 + i); func_80047804(id, ...)`. The extra
statement moves the pointer's allocno ahead of the counter's in `global_alloc`'s order, so
the pointer takes `$s0` and the counter `$s1`. Every `for`-init, declaration-order, `while`
and `register` spelling leaves it swapped; the named argument does not. Verified: the two
remaining words were `b {.L8001B734}` where the splat `.s` marks that label `jlabel`
(`.globl`), so the target object keeps an unresolved `R_MIPS_PC16` and `tools/match.py`
compared placeholder `0xFFFF` against our folded `0x13`. The disc word is `0x10400013`
(offset `0x13`), i.e. the compile was already byte-identical; `match.py` now resolves
`R_MIPS_PC16` to the symbol address and compares it with the folded branch target.

**`func_8001B238` (90 words) — 31 of 90 with a correct structure, parked.** Drafts:
`work/cand/b238-t4.c` (31 diffs, 0x164 vs 0x168) and `b238-t5.c` (44). What is established:
* the head to `0x8001B2F8` is exact, including the `D_8008A088 == 0xFFFF` init block and
  `D_8008ADBC = max(D_6040, D_16A8)`;
* the switch is `case 0` / `case 1` / default, and the *default returns 1* — the `1` is the
  constant gcc already materialised for the second `beq`;
* both case tails end in the same shape, `1` if the tail pointer/global compare fails and
  `0` if it matches, and gcc cross-jumps them into one block at `0x8001B384`
  (`bne $v1,$v0,.L8001B390` / `addiu $v0,zero,1` / `.L8001B38C: addu $v0,zero,zero`).
  Retail reaches that block with a `j`, so the two tails must be *separate* statements in
  the source that the compiler merged — `return a != b;` in both cases produces the
  cross-jump but with `xor`/`sltu` instead of the branchy form;
* the case-0 early exit `beqz $v0,.L8001B38C` shares the same `addu $v0,zero,zero` block,
  which only happens when the `0` is a *value stored to a result variable* used by the
  shared `return`, not a `return 0;` in place (draft `t4` reproduces that branch exactly);
* the residual defects in `t4`: the result variable lands in `$v1` where retail uses `$v0`,
  `memset`'s third argument comes out as `addu $a1,$v1,$zero` instead of `$zero` (the
  constant `0` is available in the result register), the read of `D_8001066C` materialises
  its address in `$v0` instead of `$a1`, and the tail is `xor`/`sltu` rather than
  `bne`/`li`/`move`.
* `-mno-split-addresses` produces exactly retail's `lui $a1,%hi(D_8001066C)` /
  `lw $a1,%lo($a1)` for that read but re-schedules the two `func_8001B1CC` calls
  (44 -> 60 diffs overall), so the flag is not the fix on its own.

**`func_8001B760` (136 words) — first draft, 123 of 136, parked.** Drafts
`work/cand/b760-v1.c`, `b760-v2.c`. Structure recovered from the disassembly: frame
`0x1E0` = `u16 ids[8]` at `0x10`, `s32 buf[96]` at `0x20`, the 0x20-byte
`func_8001D9C8` descriptor at `0x1A0`, saved registers at `0x1C0`. `tp = func_8002C3C0(arg1, 0)`
is the early-out; `ids[0] = D_8008AE14 + arg1`; `key = (*(u32 *)arg0 >> 8) & 0x1F`; the scan
takes ids whose `(v >> 4) & 0xF` is 3 or 4 (`(x - 3) < 2u`), whose `(v >> 8) & 0x1F == key`
and which are not `arg1`, writing `ids[(v >> 12) & 0xF]` and tracking
`last = max(last, (v >> 13) & 0xF)`; then one `func_8002C4E4(&buf[len], id, 0x5F - len, 0)`
per id with `buf[len] = 0`, `func_80034C20`/`func_80034D4C` copies of `ids[last + 1] * 2`
bytes and `buf[len] * 4` bytes, and a `0xA000`/`0xA008` descriptor whose `+4` word is
`tp + 5`. The blocker is one saved register too many: the drafts use `$s0`-`$s6` while
retail uses `$s0`-`$s5` (ra at `0x1D8`), so every offset from the prologue on shifts; the
drafts also come out 8 bytes short (0x218 vs 0x220). Reducing distinct locals and reusing
the same variable for the late `func_80034C20` results did not shake the extra register out.

## Pass 3 (`func_8001B238` only)

Best draft is still `work/cand/b238-t4.c`: **31 of 90 words, 0x164 against 0x168** (one word
short). Every other spelling tried this pass is worse or identical:

| draft | shape of the case tail | result |
|---|---|---|
| `b238-t4.c` | `r = 0;` at case entry, `r = (a != b)` inside the guard | 31 |
| `b238-t5.c` | `if (a != b) r = 1; else r = 0;` inside a guard holding the body | 44 |
| `b238-w1.c` | `r = (a != b) ? 1 : 0` | 31 |
| `b238-w2/w3.c` | `s32 *ip = (s32 *)D_8001066C; ... *ip` | 31 |
| `b238-z2.c` | `r = 0; if (a != b) r = 1;` inside the guard | 31 |
| `b238-z3.c` | `if (a != b) { r = 1; break; } r = 0;` | 31 |
| `b238-y1/y3/y4/y5.c` | `r = 1;` preset, early exit `r = 0; break;`, four tail variants | 82 |

The `31` group is one and the same compile: gcc canonicalises every one of those tails to
the same `xor`/`sltu`. The permuter agrees — `tools/permute.py func_8001B238 --run -j4` ran
**3751 iterations** and its best was score 860, never zero; it only ever found statement
order shuffles inside the case bodies.

**The wall, stated precisely.** Retail's shared tail is

```
8001B384 bne   $v1,$v0,.L8001B390     ; epilogue
8001B388 addiu $v0,$zero,0x1          ; delay slot
8001B38C addu  $v0,$zero,$zero        ; also the target of the case-0/case-1 early exits
```

i.e. `if (v1 != v0) r = 1; else r = 0;` with the `1` in the branch delay slot and the join at
the epilogue. `tools/cc.py` on a synthetic comparison shows gcc 2.8.1-psx emits
`xor`/`sltu` for **every** C spelling of a comparison — `return a != b;`,
`if (a != b) return 1; return 0;`, `if (a != b) r = 1; else r = 0; return r;`,
`r = (a != b) ? 1 : 0;`, the goto form, and the "statement after the if" form all give
`xor $2,$4,$5 / sltu $2,$0,$2`. So the branchy form cannot be produced by a source shape;
it is the *setcc conversion being impossible in retail's CFG*. The conversion needs the
then/else arms to be a private diamond, and in retail the `r = 0` block is a merge point
shared by the case-0 and case-1 early exits — so `jump_optimize` left the diamond alone and
`jump2` cross-jumped the two identical compare-block tails (`j .L8001B384` from `0x8001B308`).

Reproducing it therefore needs the source to make the early exits land in the same `r = 0`
block *before* the jump pass runs, which is a CFG-ordering decision, not a statement shape.
Every C arrangement tried either puts `r = 0` inline per case (so the tail becomes a private
diamond and gcc sets `cc`), or presets `r = 1` before the switch (which costs the whole
function 82 words by moving the prologue).

Remaining differing words in `b238-t4.c`, all downstream of that one decision:

```
8001B284  addiu $v0,zero,1        vs  addiu $v1,zero,1     (switch constant register)
8001B288  beq   $a3,$v0,..        vs  beq   $a3,$v1,..
8001B290  j     .L8001B390        vs  j     .L8001B38C     (one word short here)
8001B2A4  nop                     vs  addu  $v1,$zero,$zero
8001B2B8  addu  $a1,$zero,$zero   vs  addu  $a1,$v1,$zero
8001B2BC/2C0/2C4   lui $a0 / lui $a1 / lw $a1,%lo($a1)   vs  lui $v0 / lui $a0 / lw $a1,%lo($v0)
8001B2D0/2D4/2D8   same pair for D_80010668
8001B2FC/300       lui $v0,%hi(D_800B9390) / lui $v1,%hi(D_8008B4F8)   (order swapped)
8001B318  beq   $v0,$a3, +0x1D    vs  +0x1C
8001B31C  addu  $v0,$zero,$zero   vs  addu $v1,$zero,$zero
8001B330/334/338/33C/348/34C/350   the same two `lui`/`lw` pairs in case 1
8001B374/378       lui $v0,%hi(func_8005737C) / lui $v1,%hi(D_8008AC28)   (order swapped)
8001B384..8001B39C  xor/sltu/epilogue copy vs bne/li/addu/epilogue
```

`func_8001B238` is therefore parked with `b238-t4.c` as the base. The next attempt should
start from the CFG question (`can the two early exits be made to share the tail's `r = 0`
block?`), not from another statement spelling — every spelling has been tried.

## Pass: smallest-unmatched sweep (func_80011B48 class)

- **func_8002DE18** — 18/18 words, 0x44 vs 0x48. Full-size miss, not a one-word residue; source shape wrong.
- **func_80032D88** — 17/17 words, 0x3c vs 0x44. Same.
- **func_80011B48** — 12/17, pure `$v0`/`$v1` mirror on both rotate halves
  (`sll $v1,$a0,4` / `srl $v0,$a0,28` in retail, swapped for us; same for the 16-bit rotate
  and the final `or`). Permuter ran 2 450 iterations, best score 75, never 0. Same class as the
  recorded "temp pool starts at `$v0` for us" note — not a source-shape defect.
- **Flag probe** (work script, discarded): `-O1` 18 diffs, `-O2` 12, `-O3` 12, `-Os` fails in cc1.
  So the residue is not an optimisation-level mismatch.

## Pass: main catch-up + size-sorted sweep

- **func_80011B3C** — not a function: the disassembly is a 3-word `dlabel` (`.word 0x0029572F`
  flagged invalid instruction). A splat classification artifact, not decompilable as C; it should be
  reclassified as data rather than chased.
- **func_80032C28** (11 words, middle 32 bits of a 64-bit product) — 10/11 with
  `(s32)(((s64)a * b) >> 16)` and 10/11 with the explicit low/high word form. The game has three
  literal `nop`s between `mult` and `mflo`, then `mflo $v1` / `mfhi $v0`; every 64-bit spelling of
  ours emits `mfhi`/`mflo` adjacent with no nops and needs extra `sra` for the sign extension.
  Three attempts spent, no fourth shape obvious.
- **func_80045828 / func_80045838** (4 and 5 words) — both are gp plumbing (`lw $gp` restore, and
  `sw $gp` to a global with an `$sp` return). They are assembler/section artifacts, not C bodies.

## Pass: post-merge sweep (main @ da69241)

Three-attempt budget applied; nothing shipped from these.

- **func_8002BCB0** (17 words, callback dispatch) — **2 of 17 words differ, twice**: the game keeps
  the `lhu 0x24(a0)` result in `$a1`, every spelling of ours puts it in `$v0` (plain `&&` condition,
  a named `u16` local, and two early returns all give the identical body). Branch shape, calls and
  frame are already exact — this is the allocno class again, worth one more look with a permuter
  before anything bigger.
- **func_80033384** (14 words, negate three words in place) — the game loads one word, negates it in
  the load-delay shadow, and only stores after all three; gcc batches all three loads first
  (10 words vs 14). The game's negate is `sub` (`neg`), ours is `subu` (`negu`) even from
  `0 - x`. Load scheduling + signedness, not source order.
- **func_80032FF4** (13 words, `a0[i] += a1[i]` ×3) — same load-batching class: game loads all six
  words into `$t0`–`$t5` then adds then stores; both the plain form and six separate locals
  interleave load/add/store.
- **func_80036F24** (13 words) — 5 of 13: the game copies `func_80036324`'s result to `$v1` and
  stores it *after* materialising the `return 0`; ours stores straight from `$v0` and the frame
  closes a word early (0x30 vs 0x34).
- **func_800382C0** (12 words) — best 6 of 12; the accumulator lands in `$a0` (coalesced with the
  dying parameter) where the game keeps it in `$v0`, so our tail needs a closing copy. Three
  accumulation shapes tried, best 6.
- **func_8002DDE0** (14 words, backwards 12-byte scan) — 15 words produced against 14; the
  `while ((u32)p >= (u32)end)` form adds a word the game does not have.

## Pass: permuter on the three register-residue units

All three were driven through `tools/permute.py` (drift-checked: the permuter's base score agreed
with `match.py` in every case), `--stop-on-zero -j8`, per-compile `timeout 30` added to the
generated `compile.sh`, ~270–400 s each.

- **`func_80036F24` — MATCH, shipped.** The agent was the declaration: `volatile u32 D_8008B144` in
  place of `s32`. The store then cannot sink into the return sequence, so the game's
  `addu $v1,$v0,$zero` / `sw $v1` after `lw $ra` falls out, and the frame closes at 0x34. The
  permuter found it at ~iteration 200 of the second run.
- **`func_800382C0` — permuter reached score 0, deliberately not shipped.** The winning shape is
  `if ((u32)v > 0x1E000) { if (arg0) return n; else return n; }` with `n = -1` hoisted above the
  test: a **dead branch** (both arms return the same value) that gcc collapses after register
  allocation. It is a compiler oracle, not the original source — `arg0` is never tested in the
  game's 12 words — and every readable equivalent I could write (`?:` in either position, and
  `if (v < 0 || (u32)v > 0x1E000)`) lands back on 6 of 12. Recorded here rather than committed.
- **`func_8002BCB0` — no improvement.** Two runs, ~2 000 iterations total, best score stayed at the
  base 10 (2 words, the `$a1`/`$v0` rename of the `lhu` result). The permuter's statement macros
  cannot reach it.

Bases and outputs are under `work/permute/<name>/` (`base.c`, `compile.sh`, `settings.toml`,
`output-*`), so the dead-branch finding for `func_800382C0` can be revisited.

## Pass: the volatile/declaration lever family, applied deliberately

The lever that closed `func_80036F24` (`volatile` stopping a store from sinking into the return
sequence) was retested on the four units still stuck on register allocation, with `tools/match.py
--src` pointed at candidate files so each shape cost one compile.

| Unit | Baseline | Volatile shapes tried | Best |
|---|---|---|---|
| `func_8002BCB0` | 2 of 17 | `volatile u16` field read; `volatile` function-pointer global; both | **2 of 17, unchanged** |
| `func_80011B48` | 12 of 17 | `volatile u32` global through the whole rotate/xor chain | **12 of 17, unchanged** |
| `func_80033384` | 14 of 14 | `volatile s32 *` parameter (11), volatile loads into locals (13), `volatile` locals (19) | **11 of 14** |
| `func_80032C28` | 10 of 11 | `volatile s64` product | **13 of 14, worse** |

The one real improvement is `func_80033384` with a `volatile s32 *` parameter: it produces the game's
interleaved `lw; nop; neg` cadence, which nothing else did. What it cannot produce is the deferred
store — a volatile parameter makes each store immediate, and the game holds all three results in
`$t0`–`$t2` and stores them only at the end. Plain locals defer the stores but batch the loads. That
pair is unreachable from one source: `func_80033384` reads like hand-written asm (splat marks its
`neg` instructions "handwritten instruction", and `func_80032C28` has the same marker plus literal
`nop` padding after `mult`).

**Conclusion for the queue:** `volatile` is a real, general lever — but only for *store placement*.
It does not move a load's destination register (`func_8002BCB0`'s `$a1`/`$v0`), which is the most
common residue left in the small units.

## Pass: sibling ranking (tools/siblings.py)

Rebuilt the queue by similarity to matched units instead of size: shared `jal` callees, address
adjacency, comparable word count. `func_8001C1DC` scored top among small units and **matched first
compile** — shipped. Triage of the 514 unmatched: 453 plain C, 43 handwritten asm, 16 `dlabel` data,
2 gp plumbing (see `work/sibling-ranking.txt`).

- **func_80029488** (29 words) — best 15. `$s0`/`$s1` take opposite roles (game: pointer in `$s0`,
  length in `$s1`) and the frame is 0x20 against 0x28, i.e. the game has one more live value than my
  draft. Tried: cached `len`, pointer-typed `p`, three declaration orders, inlined vs named buffer.
- **func_8001D5B0** (28 words) — best 12. Everything matches up to the tail; the game copies the
  `func_8001D540` result into `$a1` and compares that with `-1`, ours compares `$v0` directly (and
  uses `$v1` for the constant), costing the extra frame word (0x6c vs 0x70). Tried: no local, named
  `r`, inverted test with early `return 0`, inlined call in the condition.
- **func_80011F84** (30 words) — best 14 (0x74 vs 0x78). Cached the loop bound into an `s32` and got
  the game's `blez`/counter shape but one word short; inline `448` strength-reduces to the game's
  `sll/subu/sll` either way.

## Pass: candidate conversion (ranking → matches)

Spent the whole budget on ranked candidates; **no unit matched**, so nothing shipped and the tree is
identical to `origin/main`. Every attempt, with its best score, in one place:

| Unit | Words | Best | What blocked it |
|---|---|---|---|
| `func_80058448` | 43 | 35/43 | `D_8008AE9C` is a pointer *variable* addressed absolutely (`lui`/`lw`); `extern u8 *` makes it gp-relative and `extern u8[16]` + cast gives the right `lui`/`lw` but gcc CSEs the base into `$s0`, while the game re-materialises it for every use — `volatile` on the load did not stop the CSE. |
| `func_80047014` | 62 | 46/62 | Everything but register *roles*: the game keeps the masked id in `$s0` and the `func_8004763C` result in `$s1`; every declaration order gave the mirror. Permuter run to 575 (base 870) in ~9 min without reaching 0, then stopped. |
| `func_80019670` | 55 | 49/55 | `D_8008AD64` must be gp-relative (`addiu $v1, $gp, %gp_rel(...)`) with the `+0x18` added at run time; `extern u8[]` gives absolute `lui`/`addiu` of the folded address, `extern u8[8]` gives gp-rel but a different loop shape (0xd0 vs 0xdc). |
| `func_8001FCB0` | 25 | 10/25 | gcc biases the pointers (`$a2 = a0+0x40`, `$v1 = a1+0xE`) and turns the `s16` copies into `lhu`; the game keeps raw `$v1`/`$a2` and uses `lh`. Tried statements, `s16` temps, and struct types — all three bias. |
| `func_800379F4` | 26 | 16/26 | loop-and-printf guard; `sltu`/`slti` shape and the `printf` argument setup differ. |
| `func_8002B194` | 31 | 27/31 | slot scan backwards; `for(;;)` with `continue` and `while ((n = p[0]))` both come up 2–4 words short of 0x7c. |

The common thread is stated in the earlier residue entry and holds: what is left in the small units is
register roles and pointer biasing, not statement shape. Sibling ranking found the right *targets*
(`func_8001C1DC` came from it and matched first compile), but the next several best-scoring candidates
all land in these classes.

## Pass: ranked candidates, shipped func_8004EECC

Every unit below was drafted from its own disassembly and compiled through
`tools/match.py --src`; none is left in the tree.

- **func_8004EECC** — MATCH (kept). 6/33 words off with the obvious spelling: gcc put the
  `u8` mask result in `$a0` (the dying parameter) where the game keeps it in `$v1`. Every
  type spelling (`u8`/`u32`/`s32` local, `u8` parameter, mask inlined twice) compiled to
  `andi $a0,$a0,0xFF`. What broke the tie was binding the table base to a named local
  (`table = D_800B03C4; p = table + idx * 2;`), which changes the allocno order so the mask
  result lands in `$v1`. Not an oracle: the readable form matches on its own.
- **func_8004E460** — 2 of 50 words. Everything matches except one scheduling swap: the
  game stores the incremented `D_80082948` before `jal func_8004F1E0` with a `nop` delay
  slot; we always spill that store into the delay slot. Same family as func_8004EECC
  (printf/exit assert, absolute globals declared as unknown-size arrays).
- **func_80015684** — 7 of 44 words, all register names in the five instructions after the
  `memset`: the game holds the block size in `$v0` and the buffer pointer in `$a0`; we hold
  size in `$v1` and pointer in `$v0`. The statement order and instruction set are identical.
  Tried: cached struct pointer (spills to `$s0`, frame 0x18 -> 0x20), fields before/after
  `D_8008AD4C`, struct-typed globals, `p = e->items`. Permuter ran 2 900 iterations,
  best score stayed at the base 45.
- **func_80019670** — 10 of 55 words, and every remaining difference is one hoist: the game
  rebuilds `addiu $v1,$gp,%gp_rel(D_8008AD64)` inside the loop and loads the slot at
  `0x18($v0)`; every struct spelling of `((Ctx *)&D_8008AD64)->slots[i]` makes gcc hoist the
  base address into `$s2` before the loop (frame 0x28, extra save). The pointer-arithmetic
  spelling `(u8 *)&D_8008AD64 + 0x18 + i*4` keeps the computation in the loop but folds the
  `0x18` into the relocation (`%gp_rel(D_8008AD64+0x18)`), which is a different immediate.
- **func_80058448** — 35 of 43 words at -O2, 27 at -O1 (with the whole tail after the last
  call matching exactly at -O1). At -O2 gcc CSEs the absolute address of `D_8008AE9C`
  (declared far, so `lui`/`lw` rather than `$gp`) into a saved register and reads the pointer
  through it; the game re-emits `lui $a0,%hi / lw $a0,%lo($a0)` at all three call sites and
  keeps only `$s0` and `$ra`. `volatile` on the object, alias-diverse casts and the
  unknown-size-array declaration all still hoist. The same address is `$gp`-relative in
  func_8001D0E4, which is why the declaration has to stay far in this file.
- **func_80047014** — 23 of 62 words, 39 of 62 instructions identical. Blockers: `arg0` lands
  in `$s1` where the game keeps it in `$s0` (so the `sll 4` result differs), and the
  `(product + 7) / 8` expands to our `bgez/sra` form where the game has
  `addiu +7; bgez; srl; addiu +0xE; srl`. Permuter ran ~900 iterations, best 715 vs base 775.
- **func_80036F64** — 52 of 67 words, 4 words shorter. Same instructions, different order and
  register assignment: the game keeps `func_8005D130`'s result in `$a0` across both bounds
  tests and reloads `D_8008B138`/`D_8008B13C` for the offset arithmetic (the second of those
  loads is dead in the game's code).
- **func_80037968** — 16 of 35 words, and the remaining difference is one fold. Nested
  `if (arg1 != 0) { if (arg1 == 1) { ... } }` reproduces the game's guard pair, and the state
  pointer is **`volatile s32 *`** — that is what makes the game reload `0($s0)` before every
  test instead of reusing one load. What is left is gcc folding the loop condition
  `*arg0 == 2 || *arg0 == 1` into `addiu -1; sltiu 2`; the game keeps the two compares
  (`beq v1,2` / `beq v1,1`, each after its own load). A `for (;;) { ... if (a) continue; if
  (b) continue; break; }` spelling makes it worse (36 words), and `!=2 && !=1` folds the same
  way.

## Pass: address-and-store placement on the four parked units (shipped 8004E460 + 80037968)

Two of the four were fully explained by one lever each, and both levers are the *same*
family: `volatile` and control flow, not types.

- **func_8004E460** — MATCH. The missing instruction was a `nop` call-delay slot: gcc kept
  sinking the `D_80082948` increment into the `jal func_8004F1E0` delay slot. Reading and
  writing the re-entrancy counter through `*(volatile u32 *) D_80082948` (declared as an
  unknown-size array so it stays absolute-addressed) pins the store before the call and
  leaves the `nop`, exactly as the game has it. Separate locals, a cached depth value and a
  `u8 idx` argument local all changed nothing; volatile-on-the-declaration alone also changed
  nothing (the qualifier has to be on the u32 lvalue).
- **func_80037968** — MATCH. Two facts: the state pointer is `volatile s32 *` (that is why
  the game reloads `0($s0)` before every test), and the loop tail must reach the head with
  two separate `if (*arg0 == N) goto again;` statements instead of `while (a || b)`, which
  gcc folds into `addiu -1; sltiu 2`. The nested `if (arg1 != 0) { if (arg1 == 1) { ... } }`
  guards are what produce the game's `beqz`/`bne` pair around the single shared exit block.
- **func_80019670** — still 10 of 55 (pointer-arithmetic spelling) / 48 (struct spelling).
  Split further this pass: expressing the slot through a struct member keeps the `0x18` in the
  load but gcc hoists the `%gp_rel` base into a saved register (extra save, frame 0x2c) and
  then strength-reduces the index away, so the loop body is `lw 0x18($s2)` instead of
  `addiu`/`sll`/`addu`/`lw 0x18`. `-O1`, `volatile` on the context, a context pointer
  assigned inside the loop and `((u8 *)&D_8008AD64)` casts all give the same 48.
- **func_80058448** — still 35 of 43 at -O2. `extern u8 * volatile D_8008AE9C[]` with
  `D_8008AE9C[0]` reads (volatile loads) does not stop gcc from CSE-ing the *address* of the
  far object into `$s0`, which is what costs the extra saved register and the 0x20 frame.

## Pass: address identity via a split base (shipped 80019670)

- **func_80019670** — MATCH. Three separate levers were needed, all readable:
  1. `count` (and the loop index) must be **unsigned**: `u32 k; k < e->count` gives the
     game's `beqz` zero-trip test and `sltu` bottom test; a signed `s32` gives `blez`/`slt`.
  2. The entry table is walked as a **pointer** (`it = &e->items[0].key; ... it += 2`), which
     reproduces `addiu $s0,$s0,8` and the `lw 0($s0)` / `lw 4($s0)` pair.
  3. The `0x18` slot offset must be added to a **temporary pointer**, not to the symbol:
     `slot = (s32 *)(D_8008AD64 + i * 4); n = *(s32 *)((u8 *)slot + 0x18);` keeps the load
     displacement at `0x18($v0)`. Every spelling that wrote the offset in the same expression
     (`&D_8008AD64[0x18 + i*4]`, `((s32 *)…)+6`, a struct member at +0x18) either folded it
     into `%gp_rel(D_8008AD64+0x18)` with `lw 0($v0)` (2 words left) or hoisted the absolute
     base into a saved register.
- **func_80058448** — still 25 of 43 (`0xa8`, want `0xac`) on the alias draft. Only three
  distinct defects remain; the 25 is one missing `nop` shifting the whole tail, plus:
  - `0x80058448` `lw $a1, %gp_rel(D_8008AC64)` — ours is `lw $v0` (and the `beqz` follows).
  - `0x800584B0` `nop` in the `beqz` delay slot — ours fills it with `lui $v0,%hi(D_8008AE9C)`
    from the success block, so every later address is one word early and the function is a
    word short. Making the load `volatile`, or the pointer slot `u8 * volatile *`, does not
    stop the fill (the movable insn is the address `lui`, not the load).
  - the three reads: game `lui $a0,%hi` / `lw $a0,%lo($a0)`, ours `lui $v0` / `lw $a0,0($v0)`
    — the address pseudo is allocated to `$v0` instead of being tied to the destination.
  Tail shape itself is right (`j` to the epilogue with `sltu` in the delay slot and the
  out-of-range `li v0,1` block skipped by the jump), so this is register identity, not source
  shape.
- **func_800379F4** — MATCH (same pass, 26/26). A single post-increment in the loop condition:
  `while (D_8008B134 != 0) { if (i++ > D_8008A598 * 10) { printf(D_80010548); break; } }`.
  Writing the counter as a normal `i++` in the `for`/`while` increment slot puts the `addiu
  $a1,$a1,1` in the loop *latch*, and gcc then allocates the D_8008A598 load to `$v1` and the
  printf format's `%hi` to `$a0` (11 words differ). Moving the increment into the condition
  makes it part of the compare, so it lands in the `beqz` delay slot exactly as the game has
  it, and the remaining register choices (load in `$v0`, format `%hi` hoisted into `$a2`)
  fall out for free.
- **func_8001A108** — 29 of 57 (`0xf0`, want `0xe4`) — the sibling-pattern draft
  (`slot = &D_8008AE00[D_8008ADFC*8]`, `p = func_80012078(3)`, `func_80014450(p)`,
  `slot[4] = D_8008AE08 + D_8008ADFC*6`, `func_80014464(p, slot)`, `slot[0] = p`, then the
  three-way dispatch and `func_8001C488(kind, 0xFFFF, p, func_8001A9DC)`) reproduces everything
  up to the dispatch. What is left is the dispatch tree itself: the game is a linear
  `beq $s2,1` / `beqz $s2` / `beq $s2,2` with the three call sites cross-jumped into one
  shared block, while gcc -O2 on a `switch` builds a balanced tree with an extra
  `slti $v0,$s2,2` (3 extra words), and an `if/else if` chain with duplicated calls inverts
  every branch (`bne`/`bnez`) and lays case 1 out as the fallthrough. Also unfixed: the slot
  pointer lands in `$s0` and the handle in `$s1` (the game is the other way round).
- **func_80034B98** — 3 of 16 (`0x3c`, want `0x40`) — closest unit of the pass. Full body
  matches (`D_8008A560 = -1`, `D_8008B0FC = *(u8 **) D_800843E8`, `func_80034BD8()`,
  `D_8008B0F4 = (u8 *) 0x801FC000`, `return 0`). The only defect is register identity on the
  far load: the game does `lui $a0,%hi` / `lw $a0,%lo($a0)` and stores `$a0`, ours does
  `lui $v0` / `lw $v1` / `sw $v1` — gcc allocated the address temp and the value temp to two
  registers instead of letting them share one. Tried: a `u8 *p` local (`p = *(u8 **)…;
  D_8008B0FC = p;`), `extern u8 *D_800843E8[]` with `D_800843E8[0]`, and reordering the two
  stores. All three give the same 3 words. Declaring `D_800843E8` as an unknown-size array is
  required (a 4-byte `u8 *` makes it small data and the game addresses it absolutely, 15
  words differ).

## Pass: -mno-split-addresses + argument pinning (shipped 8001FCB0)

Three findings this pass, two of which convert walls that had resisted five passes:

- **`-mno-split-addresses` is the flag family for "one register" far loads.** When a
  non-small-data symbol is loaded into a register, gcc splits the address into a temp
  (`lui $v0,%hi` / `lw $a0,%lo($v0)`). The per-file flag
  `/* cflags: -mno-split-addresses */` (already used by 11 units) makes it emit the game's
  single-register two-line form (`lui $a0,%hi` / `lw $a0,%lo($a0)`), which also cannot be
  scheduled into a preceding branch delay slot — that is what both
  `func_80058448` (25 words -> 2 words) and `func_80034B98` were missing.
- **A value that is also passed as a call argument pins its register.** `func_80058448`'s
  remaining 2 words were `lw $a1` vs `lw $v0` for `D_8008AC64`: the flag is passed as the
  second argument of `func_80016470(D_8008AC60, D_8008AC64)`, which pins it in `$a1` across
  the test. Declaring that call with one argument leaves the load in `$v0`. Same lever made
  `func_80034B98` exact: the loaded pointer is handed to `func_80034BD8(p)`, which is why the
  game has it in `$a0` (`a0` is still live at the `jal`).
- **func_8001FCB0** — MATCH (shipped). Indexed bases (`arg0 + i * 8 + 0x3C`) instead of
  walked pointers keep the game's offsets, an `s32` temporary keeps the loads `lh` instead of
  `lhu`, and hoisting `dst = arg0 + i * 8` into a local swaps the two induction pointers into
  the game's `$v1`/`$a2`.

### Blocked, and why (both are repo-rule impasses, not source shape)

- **func_80058448** — with `-mno-split-addresses` and the two-argument `func_80016470` the
  function is byte-for-byte a MATCH (43/43) *if* the three reads of `D_8008AE9C` are three
  distinct declared objects (`extern u8 D_8008AE9C_ptr[] __asm__("D_8008AE9C");` and two more
  aliases). With one declaration gcc CSEs the symbol address into `$s0`
  (`lui $s0,%hi` / `addiu $s0` once, then `lw $a0,0($s0)` at all three sites) — 33 of 43 words,
  frame 0x20 instead of 0x18. `tools/scan.py` rejects inline asm ("asm blocks fake a match"),
  and no allowed per-file flag (`-fno-strength-reduce`, `-fno-schedule-insns`, `-fno-inline`,
  `-O1`, `-G0`) stops that CSE. `volatile` on the pointer slot, on the loaded value or on the
  object does not stop it either (it adds a saved register instead). So this unit needs either
  an approved alias mechanism or a `-fno-gcse`-class allowed flag.
- **func_80034B98** — also a byte-for-byte MATCH with `-mno-split-addresses` and
  `func_80034BD8(p)`, but only when the final store writes the literal `(u8 *) 0x801FC000`
  (the game's `lui $v0,0x801F` / `ori $v0,$v0,0xC000` is a numeric constant, not a `%lo`
  reference). `tools/scan.py` rejects literals in 0x80010000..0x801FFFFF and asks for
  `D_801FC000`; with `extern u8 D_801FC000[]` (and a matching `config/symbol_addrs.us.txt`
  entry) gcc emits `addiu $v0,$v0,%lo(D_801FC000)` instead of `ori`, plus a different `lui`
  slot — 3 of 16 words. The rule would need to allow addresses at or above 0x801F0000 (the
  loaded image ends below it), or the constant needs an approved spelling.
- **func_800494A4** — 33 of 32 (`0x88`, want `0x80`). Body is understood
  (`D_8008A8EC = func_80034C20(D_8008A800[0] * 4); for (i = 0; i < D_8008A800[0]; i++)
  D_8008A8EC[i] = func_80034C20(0x80); D_8008A8F0 = 1; func_80049530();`), but gcc hoists the
  *address* of `D_8008A800` into `$s0` (`lui $s0,%hi` / `addiu $s0`) where the game re-emits
  `lui $a0,%hi` / `lw $a0,%lo($a0)` at all three sites. `volatile` on the object adds a second
  saved register (0x98), and `-mno-split-addresses`, `-fno-strength-reduce` and
  `-fno-schedule-insns2` all leave it at 33 — the same address-CSE-into-a-saved-register wall
  as `func_80058448`.

## Pass: scan-policy audit (no new aliases, no flag dodges)

Both units left last pass were re-tested against the project's own symbol configuration
instead of `__asm__` aliases. The conclusion is unchanged and now has the direct evidence:

- **func_80034B98** — naming the address properly does not produce retail's encoding.
  With `extern u8 D_801FC000[];` plus a `D_801FC000 = 0x801FC000;` line in
  `config/symbol_addrs.us.txt` (a legitimate absolute symbol, linkable), gcc emits
  `lui $v0,%hi(D_801FC000)` / `addiu $v0,$v0,%lo(D_801FC000)` — 3 of 16 words differ: the
  `ori` is an `addiu`, and the `lui` moves above `lw $ra`. Retail's
  `lui $v0,0x801F` / `ori $v0,$v0,0xC000` carries **no relocation at all** (splat printed
  `(0x801FC000 >> 16)` / `(0x801FC000 & 0xFFFF)`, not `%hi`/`%lo`), so the original object held
  a compile-time constant, not a symbol reference. `ori` is unreachable from any symbol
  spelling: `%lo` is sign-extended and the assembler emits `addiu` for it, while `ori` is only
  produced for a constant whose low half has bit 15 set (here 0xC000). `tools/scan.py` rejects
  exactly that constant (`hard-coded address 0x801FC000`). With the symbol the rest of the
  function is exact; the unit is a true match blocked by the guard's literal rule, and moving
  the constant into a header or hiding it behind arithmetic would be the "shape the checker
  misses" this pass is not allowed to ship. Left unmatched, evidence here.
- **func_80058448** — a single honest declaration cannot stop the address CSE. Matched shapes:
  `extern u8 *D_8008AE9C[]` with `D_8008AE9C[0]`, `extern u8 D_8008AE9C[]` with
  `*(u8 **)D_8008AE9C`, and the same at `-O3`: all three are 33 of 43 words, size 0xB0 against
  0xAC, because `lui $s0,%hi` / `addiu $s0` is hoisted once and the three sites become
  `lw $a0,0($s0)`. `-mno-split-addresses` alone does not prevent it (CSE re-introduces the
  split), `volatile` on the object adds a second saved register, and the only shape that
  matches is three declarations of the same address, which is the banned alias in another
  spelling. Left unmatched, evidence here.

### Shipped this pass: func_8001F4E8 (26/26)

The 2-word wall was an argument, not an allocation: the popped word is the **second argument**
of `func_8004912C` (`$a0` = flags, `$a1` = command word — its body ORs `$a1` into the command
and masks `$a0` with 4). Passing it there leaves it in `$a1` exactly where the game has it.
Second piece: the state test is two nested compares (`if (v < 3) if (v != 0)`); `v < 3 && v != 0`
in one condition folds to `addiu -1; sltiu 2`. The same nested-if shape also reproduces
`func_8001F3D4`'s entry (`sltiu $v0,$v1,3; beqz; bnez $v1`).

### Near misses (fresh ranked candidates, three attempts each)

- **func_8001F3D4** (37 words) — best 28 of 37. Single shared "zero" block reached from both the
  state test and `c == 0x80`, and the trailing `return 0` removed (the game leaves `$v0` alone, so
  the unit is `void`). Everything matches except block order: the game lays out
  body → zero block → else, gcc 2.8.1 lays out body → else → zero block, and picks `beq` where the
  game has `bne`. Reached by `if (state >= 3 || state == 0) { ...; if (c != 0x80) { ... return; } }`
  plus the zero calls at the end; a goto would fix the order but is not a shape to ship.
- **func_8002B194** (31 words) — best 25 of 31. Loop is `for (i = 9; i != -1; ...)` over 0x24-byte
  records from `D_800A1C90+0x144`, `memset(p, 0, 0x24)` and `*p = 1` on a zero record, returning
  `i & 0xFFFF`. The game rematerialises `-1` into `$v0` in the loop's top delay slot; gcc 2.8.1
  hoists it into a live register before the loop (rematerialisation choice, not statement order —
  tried `for`, `do/while`, `if (--i == -1) break`, `i != -1`, `-O1`, `-fno-*`).
- **func_80032FF4** (13 words) — best 12 of 13 (only `jr` matches). Three-element vector add; the
  game loads all six words into `$t0`–`$t5` before any add or store, gcc 2.8.1 interleaves
  load/add/store per element because it cannot prove `arg0` and `arg1` do not alias. Six explicit
  locals, sums-then-stores and `-fno-schedule-insns(2)` all give the interleaved form.
- **func_80036F64** (67 words) — best 53 of 67, aborted: body understood (stream read of 0x800-byte
  blocks into `*(s32 *)(s0+0x14)` with `func_8005D130`/`func_80034D4C`/`func_8005D02C`, then a
  callback at `+0x24`), but the game reloads `D_8008B138`/`D_8008B13C` where my draft reuses live
  registers — the same allocno class, too many words to converge inside the pass budget.

## Pass: 0x8001D-cluster, batched PR

Three shipped: `func_8001F4E8` (merged as #116), `func_8001D340` and `func_8001DCF8` (one PR).
Two levers did the work:

- **A shared tail is a `break`, not an early `return`.** `func_8001D340` wanted one `return 0`
  that both the empty-range test and the exhausted counter reach; writing the counter as
  `if (--i == -1) break;` inside `if (count != 0) { for (;;) { ... } }` reproduces
  `beqz $a1, tail` / `bnez $a1` / `bne $v1, $a1` and lets `-1` sit in a register across the loop.
  The same shape is what `func_8001F4E8` needed for its state test (nested compares).
- **Invert the condition so the fallthrough is the block the game falls into.** `func_8001DCF8`
  only matched after the non-flagged test was written `if ((arg1 & 0xFF) == 0)`: the pointer copy
  became the fallthrough and the default-table address the branch target.

Near misses left:

- **func_8001F3D4** — 28 of 37. Entry and both call sites match; the game lays the blocks out
  body → zero → else, gcc 2.8.1 lays out body → else → zero (and picks `beq` for the game's `bne`).
  One shared zero block needs either a `goto` or cross-jumping that this compiler does not do at
  that distance; not shipped on a shape that only works by moving the label.
- **func_8001D804** — 10 of 23, everything matches except the destination register
  (`$v1` where the game has `$v0`) in the 16-byte record copy loop over `D_8008AEC4 + index*0x44`.
  Struct-copy form (`*dst = *src`) reproduces the load/store batch; hoisting the base into a local
  fixed the load order but not the destination allocno.

**Closed as policy-blocked** (do not re-attempt): `func_80034B98` needs a compile-time constant
address the scan bans (a symbol yields `addiu %lo`, never `ori`), and `func_80058448` needs three
declarations of one address to defeat gcc's address CSE. Both have their evidence above.

## Pass: block layout + operand order (0x8001F3D4, 0x8001D3B4)

Both of last pass's one-defect units closed, and the defects turned out to be two more levers:

- **Where the shared block sits in the source decides the block order.** `func_8001F3D4` needed
  body → zero → else with `bne`. Declaring the zero path *inside* the `if (c == 0x80)` test and
  jumping to it from the state test (`goto zero`, the funnel idiom from
  `docs/MATCHING_GUIDE.md`) puts the label exactly where the game has the block, and gcc then
  emits `bne` with the zero block as the fallthrough. Declaring it after both tests gives
  body → else → zero with `beq` (32 of 37), and duplicating the block does not cross-jump
  (also 32 of 37). The other two pieces: the state test must stay two nested compares
  (`state < 3`, `state != 0`; one `&&` folds to `addiu -1; sltiu 2`), and the second cursor
  advance is `*(u8 **)(arg0 + 0x24) = p + 1` rather than `p++` (which shares the register instead
  of `addiu` into a fresh one).
- **Compare with the parameter first.** `func_8001D3B4`'s `bne $a0, $v0` / `beq $a1, $v0` only
  appear when the C is `key == p[0]` / `value != p[1]`; `p[0] == key` swaps the operands. And the
  append must read the cursor global **once** (`end = (s32 *)D_8008AEA8; end[0] = key;
  end[1] = value; D_8008AEA8 = (s32)(end + 2);`) — two reads of the global in source gives two
  `lw %gp_rel` and 9 differing words.

Still open (both one defect each, both characterised):

- **func_8001D804** — 10 of 23, permuter budget spent at base score 120 with no improvement.
  Everything matches except the destination register of the 16-byte copy (`$v1` against the game's
  `$v0`) and one load-order slot: the game issues `andi` (the `u16` index truncation), then
  `lw D_8008AEC4`, then the `index * 0x44` chain ending `addu $v0, $v0, $v1`; every spelling tried
  (`base` local, inline, offset-first, `u8 *` intermediate, struct copy) keeps the sum in the
  base's register.
- **func_8001D540** — 29 of 28 words, two words long. The `flag == 0` path wants the game's
  `bnez $a2` delay slot filled with `addiu $v0, $a3, 8` (the first half of `p + 8 + *(p + 4)`);
  writing the statement as one expression leaves a `nop` there, so the original likely computed the
  `p + 8` part before the branch.

## Pass: s32-offset add + do-while copy (shipped 8001DB74, 8001F3D4, 8001D3B4)

- **The 0x44-stride record pointer is an `s32` add with the offset first.**
  `rec = (u8 *)(idx * 0x44 + (s32)D_8008AEC4)` — casting the gp-loaded base to `s32` and
  writing the byte offset as the *left* operand keeps gcc's source operand order, so the
  walker coalesces into the multiply accumulator register instead of the loaded base. The
  pointer-typed spelling `D_8008AEC4 + idx * 0x44` canonicalises to base-first and flips the
  add's destination register. This is what closed the last 2 words of `func_8001DB74`.
- **A redundant `andi` on a `u16` load comes from naming the loaded value.**
  `u16 idx = *(u16 *)(arg0 + 2); ... idx * 0x44` emits `lhu; andi $v0,$v0,0xFFFF; sll...`.
  Reading the field inline inside the multiply (`*(u16 *)(arg0 + 2) * 0x44`) drops the mask
  and the whole body lines up. Same for `(s32)idx`.

### func_8001D804 — 8 of 23 words; add destination register

Body is exact apart from one register: the record pointer's first add. The game has
`addu $v0,$v0,$v1` (destination coalesced into the `idx * 0x44` accumulator `$v0`, base in
`$v1`); every source shape tried coalesces into the loaded base instead —
`addu $v1,$v0,$v1` with the same operand order — and the four loop stores plus the tail
`lw/sw` follow the pointer into `$v1` (tail also loads `$v0` where the game loads `$a3`).
Tried: pointer-typed add, `s32`/`u32` casts with either operand first, named `base`/`idx`/
`off` locals (which do reproduce the game's `andi; lw; sll; addu; sll; addu` instruction
order), `Quad` struct copy vs four scalar stores, `dst = (Quad *)D_8008AEC4; dst += idx`,
and the `memcpy`-style `u8 *` variant. Note the same `s32`-offset lever *does* flip the
destination in `func_8001DB74` (shipped) — the difference is that there the walker is a
one-shot `rec + 8`, while here it is the loop pointer with a longer live range, so the
coalescing tie goes to the base. Same class as `func_80058448`/`func_800494A4`: address
identity decided by an allocno tie, no allowed flag reaches it.

## Pass: branch polarity by source layout + the temp-then-copy prologue (shipped 8001FFB4)

- **A shared stage is reached by writing the inequality test first.** `func_8001C4BC`
  (`if (a->f4 != b->f4) { if (...) return -1; return 1; } ...`) reproduces the game's
  `beq`-to-the-second-stage layout exactly; the ternary spelling swaps it for `bne` and puts
  the ordering block in the fallthrough.
- **A `Table` of 0x10 bytes needs its own padding member.** `{s32; s32; u16;}` is 12 bytes and
  the index scale comes out `sll 1; addu; sll 2` instead of the game's single `sll 4`.
- **`func_8001FFB4`** — MATCH (shipped). `p = D_8006F2C0; dst = p + 8; rec = p;` — computing
  the `+8` **before** the copy forces the copy (`addiu s1, v0, 8` then `addu s0, v0, zero`);
  writing `rec = p` first lets gcc coalesce and derive `dst` from `rec`, which then loses both
  the copy and the game's callee-saved assignment (`s2` counter, `s1` dst, `s0` rec).

### func_8001C4BC — 18 of 33 words; register identity only

Instruction sequence, offsets, branch targets and sizes are identical; every remaining
difference is the register name. Game: `a` in `$t0`, `b` in `$a3`, table base in `$v1`,
`ta` in `$a2`, `tb` in `$v0`. Ours reuses the incoming argument registers (`a` in `$a3`,
`b` in `$a2`) and puts the base in `$a0`. Tried: both statement orders (a/b, ta/tb), a named
`base` local, `s32`/`u32` for the sums (u32 gives `sltu` where the game has `slt`), declaration
orders, and every ternary/if spelling of the two three-way compares. The `!=`-first spelling is
the one that matches the *layout*; the allocation of `a`/`b` to temps rather than arg registers
is the open defect.

### func_8001D4DC — 20 of 21 words; mode-0 fallthrough into the shared tail

Game: `beqz` on mode 0, `addu $a3,$a0,$zero` in its delay slot, `beq` on mode 1, `j` to a
separate `jr $ra; nop`, and `sll $a0,$a2,2` in each predecessor of the shared tail. Ours never
copies `arg0` into `$a3` (it puts `n * 4` in `$v0`, so `$a0` stays free) and picks a different
block order. Tried: if/else-if, the reversed if/else-if, `switch(mode)` with `case 0`/`case 1`
(closest at 20/21), the retail block order expressed with `goto`, and a shared `tail:` label.
The `$a0`-for-`n*4` choice is what forces the `$a3` copy; no allowed spelling reached it.

## Pass: func_8001D620 ships; the two "one-defect" units are not

**func_8001D620 — MATCH (shipped).** The lever is the cursor *reload*: after the
`D_800928C4` table walk the game re-reads `arg0+0x10` into a fresh pointer to compute the
next record (`next = *(u8 **)(arg0 + 0x10); size = *(s32 *)(next + 4); next += 8 + size;`).
Carrying the cursor in a local across the table loop instead lets gcc keep it in a saved
register, which loses the reload and one whole register of the frame.

### func_8001C2F0 — 19 of 49 words, and the defect is now known exactly

The body is right: sequence, offsets, branch targets, delay-slot fills and the frame size all
match. What differs is the *callee-saved numbering* — two adjacent swaps:

    game : s4=arg0  s3=arg3   |  s7=flag  s6=arg2
    ours : s3=arg0  s4=arg3   |  s6=flag  s7=arg2

Retail's prologue also spills in the order s2, s5, s7, s4, s0, s3, s6, ra, s1 where ours
spills s2, s5, s6, s3, s1, s7, s4, s0, ra — the same two swaps seen through the frame. Tried
this pass, all `match.py`-verified: hoisting `a = arg1 & 0xFFFF` out of the branch **42/49**;
inverted condition with the two-call form first (`i != 0 && flag == 0`) **26/49**; a
`s32 f = flag;` local **19/49** (unchanged); a `u32 a3 = arg3;` local **19/49** (unchanged).
Local existence and use order do not move this, so the next attempt needs a lever that
changes pseudo *numbering*, not local count.

### func_8001C4BC — 20 of 33 words, permuter exhausted (59 candidates, best score 30)

A comparator: two nodes, each indexing a `Table` array, comparing `f4` then `f8 + node->f4`.
Every sequence, offset and branch target matches; the game holds `a` in `$t0`, `b` in `$a3`
and the table base in `$v1`, while every spelling reuses the argument registers. The permuter
ran from the best layout (the `if (a->f4 != b->f4) { ... }` two-stage form, not a ternary) and
its best candidate is the trivial `x = ta->f4;` hoist at score 30 — no progress. Treat the
"arguments out of the argument registers" framing as wrong: nothing tried changes the
mapping, so a future pass should look for a different expression tree rather than a reshuffle.

### func_8001D4DC — 19 of 21 words differ, size 0x50 vs 0x54: **not** a one-instruction defect

A previous pass recorded this as "the missing `move $a3,$a0`". It is not: the frame is 4 bytes
short, so the whole body is compiled differently. The permuter ran 212 candidates from the
closest `switch (mode)` layout and never beat score 1015. Whatever the game's source was, it
keeps a value in `$a3` across the switch and computes `n * 4` in `$a0`; both of those need a
different expression tree (the scaled index is the likely cause) and no local/ordering tweak
tested reaches it. Rank it as a mid-size unit, not a near-miss.

### func_8001D804 — closed for this pass

Fourth pass without progress past 8 of 23 words (three shape passes plus a full 2400-iteration
permuter run at score 50). Not re-attempted this pass, as instructed.

## Pass: queue corrected, func_80011F84 ships, eight measured misses

**The queue was the bug.** `asm/nonmatchings/game/*.s` holds 1235 files for 477 unmatched
functions, so drafting from it wastes a pass. `work/unmatched.py` now derives the real queue
(game `func` rows of `config/functions.us.csv` minus `src/funcs/*.c`) and cross-checks the
result against `tools/progress.py` before printing anything:

    python work/unmatched.py --check     # cross-check: OK
    python work/unmatched.py --n 40      # smallest first, parked units last

**func_80011F84 — MATCH (shipped), first try.** The allocation is `D_80089F44 * 0x1C0`
bytes (`n*7*64`), memset to 0xFF, then the first word of every 0x1C0-byte record is zeroed.
The lever: keep `D_80089F44` as a *global re-read at each site* (the game loads it three
times) instead of caching it in a local.

### Measured misses, with the exact residue (no re-derivation needed)

- **func_80015684 — 7 of 44 words.** Everything matches except the tail's register names: the
  game keeps the allocation pointer in `$a0` (`lw $a0,D_8008AD34; sw $a0,D_8008AD4C;
  sw $zero,0($a0); sw $zero,4($a0)`) and the size temp in `$v0`; every spelling tried puts the
  pointer in `$v0` and the size in `$v1`. Best shape: local `p` for the head (so the head
  stores reuse it), `s32 *h = (s32 *)D_8008AD34` re-read from the global after `memset`, and a
  separate `s32 sz = D_8008AD44 - 0x10`. Declaring `h` before/after `p`, one temp versus two,
  and computing the size before/after the pointer load all leave the same 7 words.
- **func_80029488 — 11 of 29.** `D_8008AFAC` must be declared `s32` (the game stores a word,
  not a halfword) — that fixed two words. What is left is the frame (0x20 ours, 0x28 game: the
  game has 8 bytes of locals no spelling produces) and `s0`/`s1` swapped (game `s0` = handle,
  `s1` = size).
- **func_800382C0 — 8 of 12.** The game keeps the running value in `$v0` end to end; gcc reuses
  `$a0` as the accumulator. `u32 v = arg0 + ((u32)(arg0 + 4) >> 7) + 0x205; if (v > 0x1E000)
  v = -1;` is the closest (10 → 8 words with the assignment instead of two returns).
- **func_80032FF4 — 12 of 13.** The game hoists all six loads then adds into `$t0`/`$t2`/`$t4`;
  gcc interleaves load/add/store per component. Both the three-statement form and named
  temporaries for `b->x/y/z` interleave.
- **func_80033818 — 14 of 13.** Three temp-swaps of an 8-word struct: the game does six loads,
  then six stores; gcc interleaves.
- **func_8002DDE0 — 15 of 14.** Reverse 0xC-stride search (`p = D_8008B060 - 0xC; while (p >=
  D_8008B05C) if (*p == arg0) return p;`): one extra frame word, values right.
- **func_800337C4 — 16 of 16.** Twelve stores of `0x10000,0,0,0` × 3; the game holds the
  constant in `$t0` and the pointer in `$a0`, gcc uses `$v1` and `$v0`.
- **func_80032D88 — 17 of 17.** Clamp `v = arg0 >> 16` to `[0x10000, 0xFFFF0000]`, index
  `D_8007F8C8[arg0 >> 5]`: values and index scale right, register allocation different.
- **func_80032C28 — 10 of 11.** `(long long)a * b >> 16` gives `mult`/`mflo`/`mfhi` but gcc's
  frame is 0x20 against the game's 0x2c (the three VR4300 multiply hazard nops).
- **func_80045828 / func_80045838 — not C.** gp save/restore trampolines: the result lands in
  `$gp`, and one returns `$sp`. No C expression produces those.
- **func_80033384 / func_80033E78 — handwritten asm** (marked in the .s). `siblings.py`
  already classes 43 units this way; do not spend attempts.

## Pass: lever sweep (work/sweep.py) over the eight near-misses — 0 flips

The driver is `work/sweep.py`; it composes each unit's axes (declaration order, cached local vs
per-site global re-read, offset-first vs base-first arithmetic, named vs inline narrow read,
folded vs nested compare, struct padding vs field sum, pointer-walk vs indexed) with the three
allowed schedule/flag settings, compiles every combination through `tools/match.py`'s own
pipeline and caches the result in `work/sweep-results.json`. 162 variants over the eight units:

| unit | pools | best variant | score |
|---|---|---|---|
| func_80015684 | 54 | decl=v-h-p-sz + palloc=local + tail=reread-*-first | 7 words |
| func_80029488 | 18 | any decl/read, default flags (this template is 15; the recorded 11 came from the `s32 D_8008AFAC` + inline-read shape) | 15 |
| func_800382C0 | 36 | **body=two-returns + `-fno-schedule-insns`** | **6 words** (was 8) |
| func_80032FF4 | 9 | body=batch-sum-store | 12 |
| func_80033818 | 9 | body=batch | 12 |
| func_8002DDE0 | 9 | body=do-while | 15 |
| func_800337C4 | 9 | body=indexed | 16 |
| func_80032D88 | 36 | decl=v + body=nested + index=shift | 16 (was 17) |

**The one lever that moved anything:** `-fno-schedule-insns` with the two-return shape takes
`func_800382C0` from 8 to 6 words — the remaining six are that the game accumulates in `$v0`
while gcc coalesces `arg0` into `$a0`, plus the inverted `beqz`. Forcing a fresh register
(`u32 a = (u32)arg0;`, `s32 a = arg0;`), writing the shifted temp first, splitting the adds, and
`-fno-schedule-insns2` all leave it at 6. That unit is a register-coalescing question, not an
ordering one, and no lever in the family reaches it.

**Everything else is unchanged**, which is the useful negative result: the residue for those
seven units is not reachable by any combination of the accumulated lever families, so future
passes should stop sweeping them and either find a genuinely new lever (pointer/alias shaping,
`volatile` lvalues, a different expression tree) or leave them parked.

Note for the next pass: `work/` is gitignored, so `sweep.py` and `unmatched.py` were added with
`git add -f` to make them shared tools.

## Pass: two mid-size cluster units tried, both stopped on register allocation

Picked from `work/cluster_list.py 8001C000 8001E400 80 240` (mid-size, matched neighbours);
the eight lever-swept units are now in `unmatched.py`'s PARKED set (16 parked total).

- **func_8001D540 (28 words) — 16 of 28.** Record-stream search: advance the cursor past
  `8 + *(s32 *)(p + 4)` unless the flag says otherwise, scan for the key, then store the cursor
  at `arg0+0x10` and return `(p - *(arg0+8)) >> 2`, else `-1`. Three shapes: the natural
  `p = p + 8 + *(s32 *)(p + 4)` (**29 of 28**, one word over — gcc reassociates to
  `size + (p + 8)`), a local `next = p + 8` (**16**), and field re-reads in the loop condition
  plus inside the return (**16**). A fourth argument changes nothing. The residue is that the
  game keeps the cursor in **`$a3`** and `end` in `$v1` with a copy in `$a2`; gcc puts the cursor
  in `$v1`. That is allocation, not shape.
- **func_8001D428 (43 words) — 40 of 43.** Registers a `0x4D524F46` chunk into the 0x14-byte
  entries of `D_80092914` (max 4, first with `used == 0`), then fills `size`, `data`
  (`arg0 + 8` for the magic form, `arg0` otherwise), `start`, `end`, and returns
  `&D_80092914[i]` (recomputed — `i * 20` in the tail, so the source indexed rather than
  returning the walked pointer). The magic constant, the load and the `0x1C0`-style arithmetic
  all match; the control-flow layout does not: the game reaches the magic-hit block by a
  **forward `beq`** with both miss paths jumping past it, while every C spelling tried emits the
  hit block first. Two shapes tried (`else if (arg1)` chain and the inverted `!=` form with the
  hit block in the `else`); stop per the two-shape rule.

## Pass: breadth-first over untouched units — 0 matches, 4 units tried

Address-order walk of never-opened units, ≤3 shapes each. All four are structurally solved and
short by one or two words, so the two-pass lesson repeats: the residue is the prologue/register
copy, not the body.

- **func_80043294** (17 w) — 6 of 17, size 0x40 vs 0x44. Fills `D_8008B38C[0..-2]` walking down
  with `src` from `D_800AAB94 + 0x780` step `-0x3C0`, then `D_8008B394 = D_800AB6D4`. Best shape:
  `i = 2; dst = D_8008B38C; src = D_800AAB94; src += 0x780; do {...} while (i >= 0);` — the
  separate `src += 0x780` statement is what keeps the `%hi`/`%lo` pair unfolded. Residue: gcc
  loads the array address into `$v0` and copies to `$v1` (`addiu $v1,$v0,%lo`), the game writes
  `$v1` directly. `-mno-split-addresses` makes it worse (14 words).
- **func_8002DE18** (18 w) — 17 of 18, size 0x44 vs 0x48. Appends a 0xC record: `rec =
  D_8008B060; next = rec + 0xC; D_8008B060 = next;` then `*(u8 **)rec = arg0; *(s32*)(rec+4) = 0;
  *(s32*)(rec+8) = D_8006F834[*(u8 *)(arg0 + 3)].f8;` (0xC-stride table). Residue: the game emits
  `addu $a1,$v0,$zero` (an explicit copy of the old pool pointer) before the bump; both the
  one-local and two-local shapes coalesce it away.
- **func_80032CF4 / func_80032D3C** (18/19 w) — 19 and 18 words differ. Identical digit loop
  (`rem |= arg0>>30; r <<= 1; if (rem >= (r<<1)+1) { rem -= (r<<1)+1; r++; } arg0 <<= 2;
  rem <<= 2;` ×0x20) differing only in the final `r >> 8` / `r >> 16`. Residue: everything.

## Pass: wide flag axis over the eight recorded bodies — 0 matches

`work/sweep.py --flags-only` crosses each unit's best recorded body with 18 flags (the whole
`allowed_cflags` set plus `-fforce-addr`, `-fforce-mem`, `-fno-caller-saves`,
`-fno-cross-jumping`, `-fno-reorder-blocks`, `-fno-defer-pop`, `-fno-delayed-branch`,
`-fno-expensive-optimizations`, and `-O1`/`-O3`/`-G0`/`-G4`). 144 compiles, **no unit reached
MATCH**, so nothing was shipped and no per-unit marker was added.

| unit | best | best flag | dead ends worth knowing |
|---|---|---|---|
| func_80043294 | 6w | `-G4`, `-O1`, `-O3` (tie with default) | — |
| func_8002DE18 | **7w** (was 17) | `-fno-schedule-insns2` | `-mno-split-addresses` 14w, `-fno-delayed-branch` 16w |
| func_800382C0 | 6w | `-O1`, `-fno-expensive-optimizations`, `-fno-schedule-insns` | — |
| func_80032FF4 | 16w | `-G0`/`-G4`/`-O1` | worse than default (12w) — do not use |
| func_80033818 | 12w | `-fno-schedule-insns(2)` | `-G0` 14w |
| func_800337C4 | 16w | `-G0`/`-G4`/`-O1` | unchanged by every flag |
| func_80032D88 | 16w | `-G0`/`-G4`/`-O1` | unchanged |
| func_80029488 | 15w | `-G4`/`-O3`/`-fforce-addr` | — |

**The one real finding: `-fno-schedule-insns2` takes `func_8002DE18` from 17 to 7 words** — the
game's explicit `addu $a1,$v0,$zero` copy of the pool pointer survives when the second scheduler
is off. That unit is now the closest of the eight and is worth one more pass restricted to its
prologue copy. Everything else is confirmed unreachable by compiler configuration, which closes
the flag hypothesis: the residue in these units is not a flag, it is the source expression tree.

## Pass: alias/volatile shaping + first 0x8003/0x8004 strike — ONE match

Shaping axes (`--shaping`) over the eight recorded bodies: plain / volatile-locals /
volatile-globals / volatile-both / address-taken, × default and `-fno-schedule-insns2`, 80
compiles. **0 matches.** `func_8002DE18` stays at 7 with volatile globals; every other unit is
unchanged or worse (`func_80029488` 15 → 23/24). Alias shaping is a dead end for these bodies.

0x8003/0x8004 first strike (untouched before this pass), four units read, three drafted:

- **func_80035810 — MATCH.** 16-bit queue wrapper at `D_8008B114` keyed by `D_8008B120`:
  `switch (D_8008B120) { case 1: p = D_8008B114; *p = v; D_8008B114 = p + 1; break; case 2: p =
  D_8008B114; v = *p; D_8008B114 = p + 1; } return v;` with `v = (u16)arg0` taken before the
  switch (that is what puts the `andi $v0,$a1,0xFFFF` in the branch delay slot).
- **func_80034824** — 11 of 20. 8-byte-stride lookup: `n = arg0[5]; i = 0; if (n) { p =
  *(u8**)(arg0+8); do { if (p[0] == arg1) return p; i++; p += 8; } while (i < n); } return
  *(u8**)(arg0+8);`. Residue: `i` counts in `$a2` in the game but `$a3`-style temporaries ours;
  the walk and both returns are right.
- **func_80035BC0** — 21 of 21 (0x50 vs 0x54). Event builder: `e = D_800A6294 + arg1 * 12;
  v = ~(((arg0[2] & 0xFF) << 8) | (arg0[3] & 0xFF)) & 0xFFFF; e[0] = 4; *(s32 *)(e + 4) = v;
  D_8008B108++;`. Everything differs, so the expression tree is still wrong (the game does
  `andi`/`sll`/`nor`/`andi` in that order).
- **func_80033714** — not attempted: it saves `$ra` in `$t9` and returns through `$t7`/`$t6`, the
  signature of hand-written or heavily-shared code.

## Pass: 0x8003/0x8004, second strike — no conversions, nine units opened

Shapes tried per unit (all miss; exact best scores):

- **func_80035BC0** (0x54): best **18 of 21** with `/* cflags: -O1 */`, otherwise **20 of 21**.
  The body is right and the gap is two `andi $x,$x,0xFF` after the two `lbu` loads, which the
  game has and gcc never emits: `(u8)` values are already known to be 0..255, so `& 0xFF`
  folds at the front end — plain `u8 *`, `s8 *` with explicit masks, `u32 hi:8`/`lo:8`
  bitfields, `u16` fields, and `-O1` all produce the same mask-free shift. Also tried: mask on
  the whole value (`& 0xFFFF` only), `e[0]=4` before/after the expression, one statement vs a
  named local. **The masks are not reachable from C under this compiler**; whatever produced
  them, source shape is not it. Sibling `func_80035C14` (0x88) has the identical two masks and
  the same block, best **33 of 34**.
- **func_80034824** (0x50): best **15 of 20** (`u8` param with `& 0xFF`, `u8 n`, `p` before `i`,
  `p` read before the guard, do-while). The game keeps `n` in `$a3` via an explicit
  `addu $a3,$v0,$zero` copy, the counter in `$a2` and the walker in `$v1`; every spelling puts
  the counter and walker the other way round and drops the copy. Ruled out this pass: `u8`/`s8`
  param, `u8` vs `s32` `n`, `i` at loop top vs bottom, `while` vs `for(;;)` vs do-while,
  `p += 8` in the increment vs the body, early-return guard before the pointer read.
- **func_80034004** (0x5C): copy-up-to-NUL-then-count, fully reconstructed; best **13 of 23**
  (`u16 n`, `arg0++`/`arg1++` split, `do { } while (n < arg2)` with a `break`, then a
  `c = *arg1` loop). Sizes 0x60-0x64 against 0x5C: the game's trailing count loop is
  `while (*arg1++ != 0) n++;` with the pointer bump in the branch delay slot, which every
  spelling here emits as a separate `addiu`.
- **func_800432D8** (0x60): best **17 of 24**. Body, stride 0x14, slot array `D_8008B384` and
  order `arg2`-first are all right; the single missing word is the game's
  `addu $a0,$v0,$zero` copy of the dequeued slot pointer, which gcc coalesces. Ruled out:
  `s32 p` with casts, `s32 *p` with `p + 5`, a separate `q`/`next` variable, `slot = &arr[i]`
  then `p = *slot`, and `s32 v` read then cast to `s32 *` — all 0x5C, one word short.
- Not attempted, and why: `func_8003332C`, `func_80033768` are marked handwritten
  (`mtc2`/`sqr`, `add` with three operands, `$ra` saved in `$t8`); `func_800333C8`,
  `func_80033428` use `lui %hi(func_80033384 + 0x38)` — an address *inside another function*,
  i.e. a static object placed there, not expressible as a C reference without that symbol;
  `func_80045828` returns `$gp` and `func_80045838` returns `$sp`, which no C produces.

Conclusion for the range: it is not uniform. What converted (`func_80035810`) was a plain
switch wrapper with no masks and no pointer copies; the rest of 0x8003/0x8004 that has been
opened is either handwritten, static-label based, or blocked on the same two residues that
blocked 0x8001C/0x8001D — redundant `andi 0xFF` masks and gcc-elided register copies.

## Pass: the micro-probe — two recipes tested, one closes a unit

Probe files: `work/probe/mask.c` (17 constructs for the `andi`-after-`lbu` signature),
`work/probe/misc.c`, `work/probe/copy.c` (eight constructs for the `addu` copy). Compiled with
`tools/cc.py c FILE /tmp/x.o --print-asm`, i.e. the exact pinned pipeline.

**Recipe A (works) — test the narrow load, assign it inside the block.** The `addu` copy appears
when the C tests the *byte* in the guard and assigns it to a wider local inside the body:

    if (arg0[5] != 0) {
        n = arg0[5];          /* u8 load -> s32 local: gcc emits addu $a3,$v0,$zero */

gcc tests the load's own register (`$v0`), then materialises the assignment as a copy into the
local's register (`$a3`) because the value crosses types. `func_80034824` matches on this
first try after nine spellings failed; the whole unit, not just the prologue.

**Recipe A does not transfer as written.** `func_800432D8`'s copy is of a loaded `s32` into a
pointer, and every spelling that assigns it inside the guard still coalesces (17/24 best).

**The `andi` signature is still unexplained.** Seventeen constructs — `u8`/`s8` element types,
`& 0xFF` on values already range-known, s32/u16/int/unsigned-char bitfields, struct fields vs
byte pointers, a union view, volatile loads, compound assignment, `(u16)` casts — all compile to
the same mask-free `lbu; sll; nor`. A `static` mask helper is not inlined (it becomes a call), so
it cannot explain a mask inside a call-free function either. Under this pin the pair of
`andi $x,$x,0xFF` in `func_80035BC0`/`func_80035C14` is **not C-reachable**; those two units were
almost certainly built by a different compiler from the pinned 2.8.1, which the repository has no
per-unit mechanism to express.

## Pass: extending the copy recipe to pointers — recipe B does not exist

Recipe A (see above) covers integer **width** crossings: a `u8` load tested in the guard, then
assigned to an `s32` local, which is what `func_80034824` needed. The units still blocked on a
missing copy all cross something *else*, so this pass probed those crossings directly.

`work/probe/copy2.c` (7 constructs, `tools/cc.py --print-asm`): `E *` global bumped by `p + 1`
with a 0x14-byte struct; the same through an `E **` slot; through `slot = &arr[i]`; an `s32`
array value cast to `E *`; an `s32` array value with `(s32)p + 0x14`; a `u8 *` view of the
returned pointer. **None emits `addu dst,src,$zero`** — gcc folds the load straight into the
variable's register and computes the increment from it, which is exactly the 0x5C-vs-0x60,
4-word-short shape every spelling of the real units produces.

Direct shapes in the blocked units, all still short by the copy:

- `func_800432D8` — 14 spellings now, best **17/24**: `s32`+casts, `s32 *`+`p + 5`, separate
  `next`, `slot = &arr[i]`, `s32` read then cast, `E *` with a 0x14 struct and `p + 1`,
  `u8 *`/`void *` array element types, `u8 *` local with `(s32)(p + 0x14)`, `u32` local (same
  width, sign change), and the `if (arg2 != 0x1000) { ... }` block form.
- `func_8002DE18` — 10 spellings, best **11/18** with the struct-pointer body (`R *p` over a
  0xC record, `D_8006F834[arg0[3] * 3]` index). The pool copy `addu $a1,$v0,$zero` never
  appears: gcc emits `lw $a1` and `addiu $v0,$a1,0xC`, i.e. the increment is computed from the
  variable rather than from the loaded pseudo.

The boundary is now measured: **2.8.1 emits the conversion copy for integer width crossings
only.** Not for `s32`→`u32` (same width), not for `u8 *`→`E *`, not for `s32`→pointer, not for
pointer→`s32`. `func_8001D804`'s `$v0`/`$v1` tie and `func_8001C2F0`'s callee-saved swaps are
not copies at all, so this lever cannot reach them; `func_80032FF4`/`func_800337C4` were not
re-opened because their recorded residue is schedule order, not a copy.

Together with the `andi` result this leaves two codegen signatures in the repository that the
pinned compiler does not produce from any C: the redundant byte masks and the pointer-width
copy. Both are most likely compiler-generation differences, and the repository has no per-unit
mechanism to express one.

## Pass: extending the copy recipe to pointers — recipe B does not exist

Recipe A (see above) covers integer **width** crossings: a `u8` load tested in the guard, then
assigned to an `s32` local, which is what `func_80034824` needed. The units still blocked on a
missing copy all cross something *else*, so this pass probed those crossings directly.

`work/probe/copy2.c` (7 constructs, `tools/cc.py --print-asm`): an `E *` global bumped by
`p + 1` with a 0x14-byte struct; the same through an `E **` slot; through `slot = &arr[i]`; an
`s32` array value cast to `E *`; the same with `(s32)p + 0x14`; a `u8 *` view of the returned
pointer. **None emits `addu dst,src,$zero`** — gcc folds the load straight into the variable's
register and computes the increment from it, which is the 0x5C-vs-0x60 shape every spelling of
the real units produces.

Direct shapes in the blocked units, all still short by the copy:

- `func_800432D8` — 14 spellings now, best **17/24**: `s32` plus casts, `s32 *` with `p + 5`,
  a separate `next`, `slot = &arr[i]`, `s32` read then cast, `E *` over a 0x14 struct with
  `p + 1`, `u8 *`/`void *` array element types, a `u8 *` local with `(s32)(p + 0x14)`, a `u32`
  local (same width, sign change), and the `if (arg2 != 0x1000) { ... }` block form.
- `func_8002DE18` — 10 spellings, best **11/18** with the struct-pointer body (`R *p` over a
  0xC record, `D_8006F834[arg0[3] * 3]` index). The pool copy `addu $a1,$v0,$zero` never
  appears: gcc emits `lw $a1` and `addiu $v0,$a1,0xC`, i.e. the increment is computed from the
  variable rather than from the loaded pseudo.

The boundary is measured: **2.8.1 emits the conversion copy for integer width crossings only.**
Not for `s32` to `u32` (same width), not for `u8 *` to `E *`, not for `s32` to pointer, not for
pointer to `s32`. `func_8001D804`'s `$v0`/`$v1` tie and `func_8001C2F0`'s callee-saved swaps are
not copies at all, so this lever cannot reach them; `func_80032FF4` and `func_800337C4` were not
re-opened because their recorded residue is schedule order, not a copy.

Together with the `andi` result this leaves two codegen signatures in the repository that the
pinned compiler does not produce from any C: the redundant byte masks and the pointer-width
copy. Both are most likely compiler-generation differences, and the repository has no per-unit
mechanism to express one.

### Correction: the five accessors are PsyQ, and PsyQ stays asm

The five units matched above (`func_8005955C`, `func_80059C80`, `func_8005CAD8`, `func_8005CAE8`,
`func_8005AE68`) are **segment psyq**, not game code. They pass every gate, but `README.md` says
the PsyQ 4.4 libraries "stay asm" and `tools/progress.py` counts game code only, which is why the
headline stayed at 607/1081 while they were in the tree. They were withdrawn rather than shipped:
converting library code is outside the project's scope and is a decision for the maintainers, not
something a pass may take on its own.

**Recipe C is still worth keeping for game units.** The `-G0` signature — `lui $v, %hi(sym)` plus
a `%lo` access instead of `lw %gp_rel(sym)($gp)` — does occur in the game segment too: grep for
`sw ... %lo(...)($at)` finds it in `func_8003246C` (twice), `func_800387C8` (three times),
`func_8002BD64`, `func_80030518`, `func_80032E94`, `func_80038864`, `func_80038970`,
`func_80038B44`. Those units are the candidates for a future pass; `func_8003246C` is 0x1D8 and
mostly a chain of calls, so the small ones (`func_80030518`, `func_80038864`, `func_80038970`)
are the place to start.

**Rule for later passes:** check the segment column before spending anything on a unit. `psyq`
means stop, and the `-G0` recipe only counts when it closes a `game` unit.

## Pass: -G0 spent on game units — one match, and a screen for the rest

**Recipe C confirmed outside the library region.** `func_8002C5FC` (0x8C, the two-level
linked-list scan over `D_800A4F08`) matched on the first attempt with `/* cflags: -G0 */`, and did
not match at all without it (35 of 35 words, 0x88 against 0x8C). So `-G0` is a real per-unit flag
in game code, not just a PsyQ quirk.

**The screen** is `work/g0_screen.py`: it walks `config/functions.us.csv`, keeps unmatched `game`
functions, and flags a unit whose assembly contains a `%lo(sym)` **memory operand**
(`lw/sw/lbu/lh/... $r, %lo(sym)($r)`) while never using `%gp_rel`. The first version counted any
`%lo`, which also caught `-G8` array bases built with `addiu`, so the operand test is what makes
the list usable: **48 candidates**, smallest `func_80032D88`, `func_8002C5FC`,
`func_8002C0B8`, `func_80032E94`, `func_8002C1B4`, `func_80032F34`. Re-run it by name before
picking work from that region.

**Misses this pass, classed:**

- `func_80032D88` (0x44, fixed-point clamp then `D_8007F8C8[(v >> 5) << 1]`) — best 0x40 against
  0x44, four spellings: the clamp itself is right (`sra`, `slti`, `slt`) but gcc 2.8.1 folds the
  table base into `addiu` and then `addu` with the index, while the game keeps `lui %at`,
  `addu $at,$at,$a0`, `lh %lo($at)` — the index added to the *hi* half. Class **base-folded
  addressing**.
- `func_8002C0B8` (0x90, the same list walked with an absolute-distance box test) — best 29 of 36
  at 0x9C against 0x90 with a `for`/`continue`/`break` body; the `goto` form is worse (0xa4).
  The `bgez`/`negu` absolute value and the two `>> 1` halvings are right. Class **loop tail
  layout** (the game re-enters the node advance from two places).

## Pass: working the -G0 list smallest-first — two units at one word, none closed

Twelve units from `work/g0_screen.py`, smallest first. Best scores and the class each fell in:

- **func_80055820** (0x88, boot init: one conditional library call, then a chain of init calls) —
  **1 of 34 words** at `/* cflags: -G0 */`. Everything matches, including the
  `if (&D_800D234C != 0)` guard (a *data* symbol's address test, which gcc keeps) and
  `func_800309C4(1000, 0, 0, 0, 0)` — the first-argument 1000 belongs to the *second* call, not
  the first. The single residue is `jal func_800C3B98`'s delay slot: the game has `nop` and
  materialises `addiu $a0,$zero,0x3E8` after it, gcc 2.8.1 hoists it into the slot. Classed
  **delay-slot fill**; `-fno-schedule-insns` leaves it at 1 word, `-fno-schedule-insns2` and `-O1`
  take it to 8. A local `t = 1000` changes nothing.
- **func_80032D88** (0x44, fixed-point clamp then a s16 table read) — best 0x40 against 0x44 over
  six spellings (`arr[i]`, `*(s16*)((u8*)arr + i*2)`, `*((s16*)(...))`, with and without the
  marker). The clamp matches exactly (`sra`, `slti`, `slt`); the residue is the base: the game
  keeps `lui $at,%hi`, `addu $at,$at,$i`, `lh %lo($at)` while gcc folds the base with `addiu`
  first. Class **base-folded addressing**, unchanged by the marker.
- **func_8002C0B8** — 29/36, 0x9C against 0x90 (`for`/`continue`/`break`); `goto` shape 0xA4.
  Class **loop tail layout**.
- **func_80032F34** (0xAC) — four 64-bit products (`mult`/`mfhi`/`mflo` with `sll`/`srl`/`or`
  recombine). Class **needs 64-bit arithmetic** — same as `func_80032C28`; unreachable from C.
- **func_80032E94** (0xA0) — same 64-bit product recombine, plus calls. Same class.
- **func_80032DCC** (0xC8) — atan2-style quadrant fixup with two globals and a table. Structures
  legible but the body is large; not attempted beyond reading. Class **not attempted (size)**.
- **func_8003571C** (0xB4) — fixed-point ratio with two divisions (`div`, `break 7`, `break 6`
  overflow guards). Legible, but every guard has to land in the same order; class **division
  guards**, not attempted beyond reading.
- **func_8004584C** (0x98) — GPU packet builder with a stack scratch buffer, `0xE1000600` tag,
  two masked merges into the packet and a pointer bump. Class **not attempted (packet layout)**.
- **func_80056FF4** (0x9C) — bitmask test then a 0x10-byte record copy loop. Class **not attempted**.
- **func_80045838** — returns `$sp`; `func_80045828` returns `$gp`. Class **out of scope (not C)**.

**Verdict on the recipe's reach:** `-G0` is real and it closed `func_8002C5FC`, but the flag is not
what most of this list is missing — 47 named candidates, and the two that came closest were one
delay slot and one base fold away, both of which `-G0` does not touch. The screen stays useful as a
ranked worklist, but the next pass should prefer candidates whose *body* is arithmetic-free.
