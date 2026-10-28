# Pass record — second leaf tranche (0x80032xxx / 0x80034C / vectors)

Population unchanged: unmatched listings with no `jal`, no `sw $sN/$ra` prologue, no coprocessor
ops, ≤120 words. 74 bodies; **12 attempted this pass, 0 converted, 10 parks with a named
residue, 2 reclassified non-C**.

## The population is not all C: `$at` is the tell

14 of the 74 leaf bodies use `$at` as a general temporary or as the base of a `%hi/%lo` symbol
access. The PSY-Q assembler only emits `$at` from its addressing macros; gcc picks a real
register. Those bodies are handwritten asm and must leave the C queue:

- `func_80032CF4`, `func_80032D3C` — `slt $at, ...; bnez $at` (hand-scheduled bit packing)
- `func_80032D88` — `lui $at, %hi(D_8007F8C8); addu $at, $at, $a0; lh ... %lo($at)`
- `func_80032C28` — `mult; nop; nop; nop; mflo` (manual HI/LO padding; its neighbour
  `func_800331FC` emits the same block with no nops, so the nops are hand-written, not compiler)
- `func_80033384` — `lw; nop; neg` per component (load-delay nops, "handwritten instruction" markers)
- `func_80043294`, `func_8003B3CC`, `func_80045838` and the rest of the 14.

Exclusion rule worth adopting in `work/enumerate.py`: unmatched body whose listing contains
`$at` → not a C target (unless the body is a `jal`-carrying form where `$at` never appears).

Separately: `func_80011B3C` is a `dlabel` (3 words of data, invalid encoding), and
`func_80045828`/`func_80045838` are CRT `$gp` reload/save stubs (`lui $gp; lw $gp, ...`), which no
C body can emit. All non-C.

## Verdicts (all parks are instruction-complete unless noted)

| Body | Words | Result | Residue |
|---|---|---|---|
| func_80032FF4 | 13 | park 12/13, size exact | six loads must be batched before the three adds and three stores; gcc interleaves per component (`lw,lw,add,sw`). Explicit six locals, a target struct and sequential statements all interleave; a temp struct spills (`0x5c`). |
| func_80035BC0 | 21 | park 21/21, 0x50 vs 0x54 | one word short and register homes differ: the game carries two redundant `andi $x,0xFF` after its `lbu`s (so the source masks a value gcc cannot bound), and keeps the element pointer in `$a2`. |
| func_800382C0 | 12 | park 6/12 | only the `lui/ori` of `0x1E000` is misplaced: a named limit local materialises it first (6 words differ, everything else exact); inline literal keeps the value in `$v1` and copies to `$v0` at the return. No spelling reached "constant at its compare, value in `$v0`". |
| func_800337C4 | 16 | park 16/16, 0x3c vs 0x40 | one word: the game copies the return pointer into `$v0` *before* the twelve stores and stores through `$a0`; every spelling of `return m` / `r = m` / int cast coalesces the two pseudos. |
| func_80033818 | 13 | park 12/13, size exact | instruction sequence identical, only register names differ (`$t0-$t5` vs `$v0,$v1,$a1,$a2,$a3,$t0`). Permuter-shaped residue; `tools/permute.py` cannot run here (no `decomp_permuter` module in this checkout). |
| func_800331FC | 27 | park 35/27, 0x8c vs 0x6c | three `(u64)a*b >> 16` results live at once spill two words to the stack; a single reused `unsigned long long` still spills. The game's six-word multiply block repeated three times with no spill was not reached from C. |
| func_80034C20 | 23 | park 5/23 (unchanged) | ternary and assign-back forms both fold to `0x50`; the join copy (`addu $a0,$v1,$zero`) still not produced. |
| func_80034C8C | 25 | park 3/25 (unchanged) | same join copy as its sibling; ternary made it worse (`0x5c`). |

## Levers that did **not** move anything this tranche

- Named constant local before the value it bounds (fixes `andi` order, breaks `lui` placement).
- Ternary `x = cond ? f(x) : x` to force a join copy (folds away, loses two words).
- Whole-temp-struct assignment to batch loads (`Vec3 t; t.f = ...; *a = t;`) — spills.
- Explicit `(u32) idx & 0xFFFF` on this tranche: no effect outside `func_8001D804`.

## Queue

`work/enumerate.py`: **376 unmatched bodies** (#167, #168 still open, so the merged count has not
moved). Leaf population 74, of which 60 are plausible C after the `$at` split — the honest
adjustment to last pass's "59 clean leaf bodies" claim is that a quarter of the tiny listings in
it are handwritten asm.
