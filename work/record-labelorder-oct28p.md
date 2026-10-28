# Label order as a lever, measured on both drafts, 2026-10-28 (xiv)

Conversions 0, bodies re-tested 2 (both kept drafts, no re-transcription), parks 2 unchanged.
Every change below was measured on its own. Pipeline green on a synced tree.

| function | words | best | size | residue |
|---|---|---|---|---|
| func_80052874 | 231 | 174/231 | 231/231 | loop clamp placement (gcc ignores source order) |
| func_8003062C | 230 | 84/230 | 230/230 | rotation-counter andi + gp-relative base; pick-chain head |

## The label-order technique, and where it stops working

The technique this pass was asked to push — read the listing's labels in address order, treat that
as the source's block order, move the draft's blocks to match — **has one confirmed hit and one
clean miss**.

**Hit (previous pass, recorded because it is the evidence):** on `func_8003062C` the loading block
moved to sit after the counter arm, matching the listing's order 0x8003078C → 0x80030800 →
0x80030928 → 0x80030968. That single move took the body from 143 to 115 differing words with the
size unchanged. Moving a block changes no instruction, so it can only pay by fixing order — and it
paid 28 words.

**Miss (this pass):** on `func_80052874` the low clamp was moved into a labelled block placed in
the source *between the init arm and the mode-decrement*, exactly where the game has it
(0x8005290C). The draft was restructured with `goto clamp` / `goto stepped` so the label physically
precedes the dispatch tail.

| shape | result |
|---|---|
| clamp duplicated in both arms, low arm inline (kept draft) | 174/231, size 231/231 |
| low clamp hoisted as a labelled block before the decrement, low arm `goto clamp` | 174/231 — **no movement** |

The disassembly confirms the block did not move: the given source still emits the decrement at
0x8005290C and the clamp inside the loop. So the technique is **not** general: gcc 2.8.1 places a
loop's exit block by its own CFG ordering, not by source position, while a straight-line block in
a chain does follow source order. The body was reverted to the cleaner duplicate-in-both-arms
shape, which is the same 174 words without the gotos.

Residue unchanged and named: `beqz $v0, .L8005290C` at 0x800529C8 — the low clamp's placement.

## func_8003062C — the two operand-form attempts, both measured wrong

The task was to write the mask before the increment and to test a scalar extern for the table
base. Both were tried, alone and in combination; both moved the numbers the wrong way and were
reverted.

| # | change | result |
|---|---|---|
| 0 | kept draft | 84/230, size 230/230 |
| 1 | `u32 idx = D_8008A389;` with `D_8008A38C[idx & 0xFF]` | 85/230 — one worse; gcc still drops the mask on a value it knows came from `lbu` |
| 2 | same with `s32 idx` | 85/230 — identical; no `andi` appears at 0x800306D0 |
| 3 | both tables as scalar externs (`extern u8 D_8008A38C;`, indexed `(&D_8008A38C)[...]`) | 185/230 @0x394 — one word short, far worse |

So the game's `andi $v0, $v0, 0xFF` at 0x800306D0 does not come from a mask on the index
expression, and the gp-relative `addiu $v1, $gp, %gp_rel(D_8008A38C)` at 0x800306D8 does not come
from shrinking the extern. Both remain open, and the honest statement is that the source spelling
for that pair is still unknown — the body is otherwise at 84 differing words with exact size.

Second residue unchanged: `addiu $v0, $zero, 0x6` at 0x800307B4, one word of arrangement at the
head of the pick chain.

## State

- attempted 2 (re-tests of kept drafts), converted 0, parks 2 — both instruction-complete
- banked: label order is evidence for straight-line chain blocks but **not** for loop exit blocks;
  the scalar-extern and index-mask spellings for the rotation table are both measured negatives
- pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`
- worktree check: 684 local = 684 upstream before and after the records commit
- queue: 130 open fresh, 227 attempted, 684 merged
