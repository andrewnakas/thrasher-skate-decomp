# pass oct28x — func_8002E4B4 ordering, and the call-heavy twin decode

## func_8002E4B4 — 106/118 held; the one shape tried made it worse

| # | shape | measurement |
|---|---|---|
| 0 | split accumulation (`sum = t[0]*d[0]; sum += t[1]*d[1]; sum += t[2]*d[2];`) | **106/118, size exact** |
| 1 | single expression (`sum = t[0]*d[0] + t[1]*d[1] + t[2]*d[2];`) | 118/118, 0x1e0 — 1 word long |

Reverted to 0.

What the diff showed, and why the ordering lever cannot close it: the game's first product lands in `$a2`
(a caller-saved temporary) while the draft's lands in `$s0`, which pushes every parameter one saved
register up — `$s0/$s1/$s2/$s3` in the game become `$s1/$s2/$s3/$s4` in the draft. Once that happens
every load and store in the body differs, which is why 106 of 118 words count as differences even though
the instruction sequence is otherwise the same shape. That is the filed allocation class — a
caller-saved versus callee-saved home for a live product — not statement order, and the ordering
changes tried here cannot move it.

## func_80026478 — the call-heavy twin, decoded once

Drafted whole from the listing in one pass: 19 calls, three axis projections with per-axis sign
handling, three local vectors built from the source's components, a normalisation through
`func_80032C54` and `func_800331FC`, then the three output vectors written through
`func_80026DEC`/`func_800330A4`.

First measurement: **109/177, size 0x280 vs 0x2c4 — 17 words short.**

That gap is structural, not allocation: the game holds the three component vectors on the stack and
re-reads them through the delay slots of the calls, where the draft materialises each copy as three
separate statements and lets gcc keep them in registers. Because the shape is 17 words wrong, the twin
substitution (`func_80026870`) was not attempted: substituting a tag and an offset into a body that is
structurally incomplete would have measured the same 17-word gap for a second time.

Residue for the pair, named: **the three stack vectors (`sp+0x20`, `sp+0x30`, `sp+0x40`) must be built by
store-then-negate sequences that the call delay slots then consume** — writing them as plain
`a[i] = src[i]` copies lets gcc keep all three in registers and loses the 17 words.

## State

Conversions 0, bodies attempted 2 (the projection re-test and the first twin), twin substitution not
attempted with the reason recorded.

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
