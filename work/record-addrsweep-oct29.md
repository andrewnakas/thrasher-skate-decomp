# pass oct29 — address-sum lever swept over the parked population

The rule under test, now stated precisely: for a **plain base-plus-offset** the accumulator must be
the base; for an **indexed** address the scaled index comes first, the base second, and any small
bias only after the whole sum has been cast to a pointer. Writing the bias inside the sum breaks it
in either order (proved on `func_80026478`, A=151 / B=4 / D match).

## Sweep: bodies parked on an address build, ascending residue, one shape each

| body | before | shapes tried this pass | best after | what is left |
|---|---|---|---|---|
| `func_800382C0` | 1 | base-accumulator `v = x + v`; inline constant; single expression with `x` first | 1 | the `lui/ori` for `0x1E000` is hoisted by us and materialised *after* the arithmetic in the game; `addu $v0,$v0,$a0` still not `$a0,$v0` — operand/schedule class, not spelling |
| `func_80056C90` | 2 | incomplete-array extern on the source record (the tell that fixes `%lo` folding) | 2 | `lui $v1` + `addiu $t0,$v1` vs the game's `lui $t0` + `addiu $t0,$t0` — the filed `la`-temp class |
| `func_80056FF4` | 2 | index-first sums at both address sites; incomplete array for the byte global; slot load inlined; `u32` slot | 2 | the two sums are now bit-identical to the game; the last two words are `lui $v0` + `lbu $a0,0($v0)` where the game reuses `$a0` |
| `func_8003BF7C` | 2 | incomplete array; sized array `[0x40]`; `u32` scalar | 2 | `u32` scalar collapses to `%gp_rel` (74 words, reverted); sized and incomplete arrays both leave `lui $v0` + `lw $a0,0($v0)` vs the game's `lui $a0` + `lw $a0,%lo($a0)` |
| `func_8002050C` | 4 | `(u8 *)(i * 16 + (s32) t->arr)` + `return (u8) i`; named `-1` local | **3** | the `addu` operand word converted (`addu $v1,$v0,$v1` now exact). Left: the `-1` limit rematerialised (`addiu $a3,$0,-1` vs `addu $a3,$v0,$0`) and the `andi` mask in the wrong delay slot. Naming the sentinel costs 17 words, reverted |
| `func_8003B3CC` | 11 (stored draft used `base` before assigning it) | repaired + `v * 0x70 + (u32) base`; symbol arithmetic without a local | 11 | index-first fixed the `addu` order; symbol arithmetic folds `+0xE0` into `%lo` (18, reverted). Left: base homes in `$v1` vs the game's `$a0`, and the `0xE0`/`0xE4` store order |

**Conversions 0 of 6.** Every surviving residue is a register home, a delay-slot choice or a
constant hoist — the address spelling moved exactly one word on one body. That is the finding: the
address-build park population is now exhausted as a spelling population; what remains in it is the
filed `la`-temp liveness class (three independent bodies, plus `func_8003BF7C` making four) and the
scheduler class on issue #17.

## Fresh drafts, address written in the winning form from the start

| body | words | measurement | residue |
|---|---|---|---|
| `func_800579E0` | 109 | 85/109, size 0x1a0 vs 0x1b4 | arm polarity fixed (`!= 4` takes the far branch, as the listing's `beq` does); the base is materialised first through a named `u8 *tbl`, which reproduces the game's `lui $v1` in the branch's delay slot; index-first sums for `a0*0x70 + tbl`, `f69*0x30 + D_800B2C7C`, `a1*4 + ent->f6A*0x28 + D_800B2CDC`. Five words short: the four-arm chain (1, 0, 2, 3 — a compare chain, not a switch, since a switch would emit `sltiu`/`jr`) CSEs the `f04`/`f08` loads that the game re-issues per arm |
| `func_80041374` | 113 | 108/113, size 0x1cc vs 0x1c4 | coarse decode only; parked at the first measurement as the cap requires |

## Tree guard fired — on my own command

`cp work/best/func_8001D804.c src/funcs/func_8001D804.c` followed by `rm -f src/funcs/...` deleted
two **tracked merged** unit files (`func_8001D804`, `func_8002FE80`). `lane/select.py list` refused
with `src/funcs has local edits` before any selection ran; both were restored with
`git checkout -- src/funcs/...`, and `685 local = 685 upstream` was re-asserted. The two bodies are
**already merged** (`func_8001D804` matches byte-exactly from `work/best`, and `func_8002FE80`
likewise) — they were still sitting in the parked corpus, so the census lists two closed bodies as
open. Check `git ls-tree origin/main src/funcs` before re-testing any parked name.

## State

**Conversions 0, bodies attempted 8** (`800382C0`, `80056C90`, `80056FF4`, `8003BF7C`, `8002050C`,
`8003B3CC`, `800579E0`, `80041374`). Two more discovered already merged and skipped.

Pipeline: scan 685 files 0 problems, gate pass, build `SLUS_009.35: OK`, tree `d73f7b93`.
