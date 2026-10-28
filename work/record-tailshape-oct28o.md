# The two named tails closed to instruction-complete, 2026-10-28 (xiii)

Conversions 0, bodies re-worked 2 (both already-parked drafts, no re-transcription), parks 2.
No new body was drafted: the two shape passes took the whole budget, and the third item in the
plan is the honest miss of this pass. Pipeline green on a synced tree.

| function | words | best now | was | size |
|---|---|---|---|---|
| func_80052874 | 231 | 174/231 | 194/231 @0x358 | 231/231 |
| func_8003062C | 230 | 84/230 | 157/230 @0x388 | 230/230 |

Both drafts sat in the records branch from the previous pass, so neither body was transcribed
again; every change below is a measured shape edit on the kept source.

## func_80052874 — the arm polarity, then the duplicate clamp

Two changes, each measured, both in the direction the numbers moved:

| # | change | result |
|---|---|---|
| 1 | the voice-attr arms written `if (!(flags & 0x200)) { clear } else { set }` with the **single shared call after the if/else** and the extra call inside the set arm, instead of two full arms | 194/231 @0x358 → 193/231 @0x374 |
| 2 | the movement clamp **written twice**, once per arm, each with its own `break`, instead of one shared `step > 0 ? high : low` test | 193 → **174/231, size 231/231** |

Change 2 is the finding: the listing contains **two** clamp blocks. The high-bound copy sits
inline after its test at 0x800529A8 and the low-bound copy is hoisted to 0x8005290C, and both end
by jumping to the attr section — so both are `break`s out of the loop, not a shared clamp with a
common exit. Writing one shared test made the body four words short and cost 19 differing words.

Change 1 is the banked arm-polarity rule applied where it had not been: the game's `bnez` at
0x800529F0 sends the 0x200-set path out of line, so the clear path is the fall-through and the
test must be written negated. Spelling it as `if (flags & 0x200) { set } else { clear }` puts the
set arm in the fall-through slot and shifts everything after it.

**Park, 174/231, size exact.** Residue is block order only: the game emits the low clamp at
0x8005290C (before the mode-dispatch tail), this draft emits it inline in the loop. Turn-on
instruction: `beqz $v0, .L8005290C` at 0x800529C8. Everything else — frame 0x70, the head to
0x80052900, and the three-continuation feed tail with its `lw $a0, 0x18($s2)` reloads — matches.

## func_8003062C — the sub-state arm's tests, then the block order

Four changes, three paying and one measurably wrong:

| # | change | result |
|---|---|---|
| 1 | case 2 restructured so the sub-state arm's tests follow the listing (`< 3`, then `> 0`, then `== 0`, then `== 4`) and the `.L80030968` continuation is **one** labelled block reached from both arms, not two inlined copies | 157/230 @0x388 → 143/230 @0x39c |
| 2 | the loading (`play`) block moved to sit **after** the 0x385-counter arm in the source, matching the listing's label order 0x8003078C → 0x80030800 → 0x80030928 → 0x80030968 | 143 → 115/230 |
| 3 | the `D_8008A368` pick written as an **or-chain** (`== 6 \|\| < 7 \|\| == 9`) with the single other value in the `else if`, instead of four `else if` arms each storing -1 | 115 → **84/230, size 230/230** |
| 4 | the two gp-relative tables declared `u8 X[8]` to force `addiu $v1, $gp, %gp_rel(...)` | 84 → 190/230 @0x394 — **reverted**, measured wrong |

Finding from change 3: a set of values that all select the same result except one is an or-chain
of positive tests in source. The else-if chain emits an extra `j` to rejoin after the last arm and
costs one word; the or-chain emits the game's `beq`/`bnez` chain into one shared have-point.

Finding from change 2: the listing's label order is evidence of the source's block order. Moving
the block — not rewriting it — paid 28 differing words with the size unchanged.

**Park, 84/230, size exact.** Residues, each with its instruction:
1. the rotation-counter block: the game masks the pre-increment value (`andi $v0, $v0, 0xFF` at
   0x800306D0) and builds the table base gp-relative (`addiu $v1, $gp, %gp_rel(D_8008A38C)` at
   0x800306D8); this draft drops the redundant `& 0xFF` and materialises the base absolutely.
2. the pick chain's leading compare: `addiu $v0, $zero, 0x6` at 0x800307B4 — one word of
   arrangement remains at the head of the chain.

## Not done

The plan's third item — one more body from the narrowed list written whole — was not started. The
two shape passes above took the session, and the narrowed list's next member is 250 words
(`func_80027CD4`), which is not a partial-job body. It is open and fresh on this tree, and its
listing has been opened once (a 0x28-stride record loader with a fixed 4-entry sub-record, a
`0x45434146` tag lookup and a table of per-entry flags) but no draft exists, so nothing is claimed
here beyond that.

## State

- attempted 2 (both re-worked from kept drafts), converted 0, parks 2 — both now instruction-complete
- new banked facts: the duplicate-clamp-in-both-arms shape; the or-chain for a one-out-of-many
  selector; label order in the listing as evidence of source block order
- measured negative: sizing the two gp-relative tables to force gp-relative addressing is wrong
- pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`
- worktree check: 684 local = 684 upstream before and after the records commit
- queue: 130 open fresh, 227 attempted, 684 merged (before this pass's two re-works)
