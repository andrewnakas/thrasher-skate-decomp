# pass oct28r — bounded: one experiment, then four whole bodies

Instruction: one experiment on the closest draft, then three untouched fresh bodies with one
measurement each, then one more if time allowed.

## Part 1 — the experiment on func_8001FD54 (and a correction to the record)

The stored draft re-measures **92/105, size 0x19c** (2 words short). The 39/105 figure written in the
previous record does not reproduce from the draft that was kept; treat 92/105 as the number.

The prescribed lever was to keep the three distance temporaries in memory without indexing:

| shape | measurement |
|---|---|
| stored draft (scalar locals) | 92/105, 0x19c — 2 short |
| `s32 w[6]` indexed block (prior pass) | 84/105, 0x1b0 — 4 long |
| `volatile s32 w[4]`, constant offsets | 94/105, 0x1e0 — 16 long |

Verdict: **the experiment did not pay.** Volatile forces a reload at every use, not the two stores the
game spends, so it costs far more than the two words it might have bought. Reverted to 92/105, parked
with the residue named: the two scalar spills of the squared distances, turn-on being whichever source
shape makes gcc 2.8.1 spill those intermediates instead of keeping them live in $a1/$t0.

## Part 2 — four untouched fresh bodies, one measurement each

| body | words | first measurement | turn-on / residue class |
|---|---|---|---|
| func_8001A550 | 106 | **33/106, size exact** | allocation — which register homes each of entry/base/i against the count in $a1 |
| func_8001D9C8 | 107 | 98/107, 1 word short | block order / loop form — the flag-and-goto scan against a do-while |
| func_8001CAA8 | 109 | 108/109, 4 words short | call-argument homing in the two nested loops; the 0x78-stride walk |
| func_800282E4 | 109 | 112/109, 4 words long | frame content — one pointer duplicated where the draft uses one, costing 4 words |

No body was given a second shape. `func_8001A550` is the one worth reopening: size exact on the first
compile with 73 words already matching, which is the profile that has converted before.

## State

Conversions 0, bodies attempted 4, experiment 1. No PR: nothing matched.

Pipeline on a clean tree: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`.
Worktree 684 local = 684 upstream; records landed through a temporary index, no branch switch.
