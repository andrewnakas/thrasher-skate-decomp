# pass oct28v — call ordering: one conversion, shipped

## func_800250B4 — **MATCH**, shipped as PR #205

173 words, zero branches, twenty-four calls. Written whole in one pass from the listing as eight
identical groups: three stack vectors at `sp+0x10`, `sp+0x20`, `sp+0x30`, each group setting the source
vector's three words, calling `func_80033714(base, v, tmp)`, then `func_80032FF4(tmp, dest)` and
`func_80024DBC(dest2, tmp)` with the two destinations alternating.

First measurement: **MATCH**. No shape iteration at all.

That is the strongest evidence yet for the selection rule this pass was built on: the body with **no
branches** converted on the first compile, where bodies of the same size and smaller frame with a
handful of branches have sat at 60-100 differing words for passes. Call sequencing with no control
flow is the shape this lane can transcribe.

Shipped from `origin/main` on branch `freebuff/func-800250B4`, commit `2100706`, one file added. scan
685/685 clean, gate 685/685 pass, build `SLUS_009.35: OK` on the branch. PR #205 with the template
body, all five provenance boxes, one "who made this" box and the agent acknowledgement ticked.

## func_8003246C — 66/118, size exact, parked

The assigned body. Three shapes, none moved the number by a single word:

| # | shape | measurement |
|---|---|---|
| 0 | initial draft | 66/118 |
| 1 | drop the `one` local, store the literal 1 in the spin loop | 66/118 |
| 2 | drop the `end` local, inline the `D_800DF16C` compare | 66/118 |
| 3 | big-object decls for `D_800843E8` / `D_80089FAC` (absolute addressing instead of the array cast) | 66/118 |

The frozen count is diagnostic: the object file shows gcc keeping `$s0` = the address of
`D_80089FAC` across the loop and materialising the constant 1 into `$s1`, where the game keeps the
constant in `$s0` and re-materialises the address. That is a choice between two equally valid
allocations of one call-preserved register, not a missing source form — the class the filed allocation
issue describes, one register home away.

## func_800403DC — 59/110, 1 word short, parked

110 words, twelve calls, nested record walk producing three output buffers. Drafted whole from the
listing in one pass; 51 words matching on the first compile with the body one word short. Residue:
where the three buffer cursors are set up relative to the inner walk. One shape only, parked.

## State

**Conversions 1 (func_800250B4, PR #205), bodies attempted 3 this pass.** Records: this file.
Queue after: 398 open, 239 attempted, 684 merged (the PR will take the merged count to 685 when
Steward lands it).
