# pass oct28w — the zero-branch class, enumerated

Instruction: mine the class that converted last pass — bodies whose listings contain no conditional
branch — and draft five or more of them.

## The enumeration result is the headline: the class has one member, and it is already matched

Parsing all 120 free listings for branch instructions (conditional branches and `j`, `jr` excluded as the
epilogue exit):

| filter | count |
|---|---|
| zero conditional branches, zero `j` | **1** — `func_800250B4`, matched last pass, PR #205 |
| zero conditional branches excluding that one | **0** |
| at most 2 branches and frame ≤ 0x38 | **0** |
| at most 3 branches with ≥ 5 calls | 2 (both 177-word twins, 19 calls, 7 saves) |

So the pure class is exhausted. The frontier of the free set, ordered by branch count:

| branches | calls | frame | saves | words | body |
|---|---|---|---|---|---|
| 2 | 4 | 0x48 | 5 | 118 | func_8002E4B4 |
| 3 | 17 | 0x40 | 20 | 172 | func_80023ECC |
| 3 | 19 | 0x70 | 7 | 177 | func_80026478 / func_80026870 |
| 4 | 4 | 0x28 | 6 | 228 | func_8003E410 |

That is a useful negative result: the conversion last pass was not the top of a long queue of similar
bodies, it was the only member of its class. Subsequent passes must expect the next-best class to be
two-to-four branch bodies, not more of the same.

## Three drafts, one measurement each

| body | measurement | turn-on named |
|---|---|---|
| func_8002E4B4 | 106/118, **size exact** | statement order inside the two projection arms — the eight products and their stack homes |
| func_800299F8 | 105/113, 5 words short | the buffer store and `memset` argument ordering at the head |
| func_800501E4 | 112/115, 9 words long | the `while` counter/offset pair at the head; gcc wants the two inductions in one statement |

No second shape on any of them. `func_8002E4B4` is the best of the three: size exact, 51 matching words,
and a pure ordering residue (it is a two-arm projection with struct copies, no allocation subtlety).

## State

Conversions 0 this pass (the shipped match was last pass's). Bodies attempted 3.

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
