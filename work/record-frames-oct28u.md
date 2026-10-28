# pass oct28u — selecting on frame size and save count instead of body size

Instruction: filter the fresh class for small frames and short save sets (two or three saved
registers), because the converting passes had little allocation surface; take three or four, one shape
each.

## The filter

The 125 fresh listings were parsed for their opening frame adjustment and prologue save stores; 116
have a frame. Sorting by frame then save count gives the whole free class a different shape from the
size ordering that has been used for the last several passes:

| frame | saves | words | body |
|---|---|---|---|
| 0x18 | 1 | 109 | func_80054354 |
| 0x18 | 1 | 118 | func_8003246C |
| 0x18 | 2 | 114 | func_8003C928 |
| 0x20 | 3 | 119 | func_80025368 |
| 0x20 | 3 | 124 | func_8003012C |
| 0x20 | 3 | 137 | func_8003599C |

Note the correlation is weak on its face: the smallest frames in the free class still carry 109-119
words. What they do not carry is five or six saved registers, which is the allocation surface the
drought blamed.

## The four bodies, one measurement each

| body | frame/saves | first measurement | turn-on / residue class |
|---|---|---|---|
| func_80054354 | 0x18 / 1 | 105/109, 10 words short | branch structure — the `s->unk0 & 0x1000` clamp path collapsed, losing the goto arm |
| func_8003246C | 0x18 / 1 | **66/118, size exact** | call-order and the `D_80089FAC` spin — everything else is a straight call sequence |
| func_8003C928 | 0x18 / 2 | 103/114, 1 word short | the two min/max clamp arms and the scratch stores |
| func_80025368 | 0x20 / 3 | 126/119, 19 words long | the `<< 5` / `* 40` index scaling was written as arithmetic the listing does with `sll`+`addu` chains |

`func_8003246C` is the useful result: size exact on a cold compile with 52 words already matching, and
its residue is a call sequence rather than allocation — the opposite profile from the two size-exact
parks this lane has been stuck on. It is a boot sequence, so its remaining differences are ordering of
independent calls, which is the most tractable class in the bank.

No body was given a second shape.

## State

Conversions 0, bodies attempted 4, PRs 0 (nothing matched).

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
Fallback for later passes: the frame/save filter is a five-line parse of the listing headers, not a
tool that needs committing.
