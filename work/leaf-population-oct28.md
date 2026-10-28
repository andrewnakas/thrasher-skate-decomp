# Pass record — leaf population (no `jal`, no saved-register prologue)

Selection rule used instead of size: from the unmatched listings on `origin/main`, keep bodies
whose assembly contains **no `jal`** and **no `sw $sN/$ra` prologue** — nothing to pair, nothing
live across a call, no save order to fight. Cap ≤90 words. That population is **59 bodies**;
the five smallest plus one family body were drafted whole and measured.

## Verdicts

| Body | Words | Result | Residue |
|---|---|---|---|
| func_8001D804 | 23 | **MATCH** (PR #167) | none |
| func_8002BA64 | 23 | **MATCH** (PR #168) | none |
| func_80034C20 | 23 | park, 5 of 23 | exact size and instruction sequence; the aligned pointer's home swapped (game keeps it in `$v1`, copies to `$a0` at the join; ours computes it straight into `$a0`). Pure register role. |
| func_800257A0 | 21 | park, 6 of 21 | exact size; walked pointer's addressing anchor: gcc folds the largest offset into the base (`addiu $v1,$a0,0x74` + negative displacements) where the game anchors on the argument (`addu $v1,$a0,$zero` + positive displacements). Same with a `u8*` walk and with a struct-field walk. |
| func_8001D4DC | 21 | park, 21 of 21, 0x48 vs 0x54 | gcc CSEs the `p+8` load across the two mode arms (the game loads it separately in each) and merges the `-1` return path; three words short on the shared tail. |
| func_80047834 | 115 | park, 114 of 115, 0x1D8 vs 0x1CC | two-case switch (mode 4 / mode 8). gcc 2.8.1 emits a jump table when case 4 is written first and a bare compare chain when case 8 is first; the game has case 8 tested first *and* an upper-bound range test (`slti $v0,$a3,9`), which no spelling reached. Arm bodies are also 12 words long. |
| func_8003332C | 23 | **excluded, not C** | GTE `mtc2`/`sqr`/`mfc2`; listing is already marked "Handwritten function". |
| func_80034C8C | 25 | park, 3 of 25 | sibling of func_80034C20 in the same allocator pair; same residue exactly: at the join the game copies the aligned pointer (`addu $a2,$v1,$zero`) and compares/stores the copy, ours uses `$v1` directly. A named copy local, a `(u32)` cast on the compare and integer align arithmetic all coalesce away. |
| func_80033E14 | 25 | park, 25 of 25, 0x68 vs 0x64 | parameters are `(src, dst)` not `(dst, src)`. Body is 12 loads then 12 stores; `*(Rec *) dst = *(Rec *) src;` with a 0x30-byte `Rec` becomes a 4-word loop (0x38), and three 16-byte chunk assignments inline but interleave loads and stores per chunk and leave one extra word. The game's all-loads-then-all-stores expansion was not reached. |

## Levers that landed (both new, both transferable)

1. **Address as an integer sum.** `u8 *dst = (u8 *) ((u32) off + (u32) base);` makes gcc emit
   `addu dst, off, base` — offset on the left. `base + off` produces the game's reverse order.
   This closed the last two words of `func_8001D804` and the `addu` operand order in
   `func_8002BA64`.
2. **Explicit narrow local + one statement per operation.** `u32 n = (u32) idx & 0xFFFF;`
   puts the `andi` first and flips the schedule that follows it (that is what closed
   `func_8001D804`, after `u16 n = idx;` left a two-word `andi`/`lw` swap). A separate `i--;`
   statement ahead of the guard is what made `func_8002BA64` load the count straight into the
   index register instead of bouncing through `$v0`.
3. **Whole-record assignment for block copies.** `*(Rec *) dst = *(Rec *) src;` with a 0x44-byte
   `Rec` produces the game's four-loads-then-four-stores + trailing word; the earlier
   `work/near-miss/func_8001D804-copybase.c` (4-word chunk walk) had the right idea but the
   wrong granularity and never matched.

## Family note: the 0x80034C allocator pair

`func_80034C20` (alloc) and `func_80034C8C` (free) are the same template: `D_8008B0F8`/`D_8008A560`
against limit `D_8008B0F4`, the same `p - ((p & 3) - 4)` align-up, and the same three-word residue at
the join — a copy of the aligned pointer into the compare/store register that no C spelling kept.
Both are instruction-complete. That copy is now the family's signature, not a per-body puzzle.

## Queue

`work/enumerate.py` on this branch: **376 unmatched bodies** (8 bodies attempted this pass, 2
converted, 5 parked with named residue, 1 excluded as not-C) (two units merged upstream since the
last record; #167 and #168 will take it to 374 when merged). Population of 59 leaf bodies still
holds; the two park-residues above (addressing anchor, register role on an exact body) are the
same class the lane has called allocator-bound, now measured on this population too.
