# pass oct28t — bounded: remaining untried loop forms on func_8001A550 and walk shapes on func_8001CAA8

## func_8001A550 — the prescribed pre-test + compound-condition loop does not work either

Best stays **25/106, size exact**.

| # | shape | measurement |
|---|---|---|
| 0 | do-while, entry = 0 before the scan (kept) | 25/106, 0x1a8 |
| 1 | entry compare before the loop, then `while (++i < n && key != *(s32 *)(base += 0x18))` with a trailing `if (i < n) entry = base;` | 113/106, 0x1c8 |
| 2 | same with the condition order swapped: `while (key != *(s32 *)(base += 0x18) && ++i < n)` | 111/106, 0x1c0 |

Both orderings are far too long: putting the pointer advance inside the condition makes gcc materialise
the advanced address as a value (it is needed in both the condition and the body) instead of using it
as an induction increment, which costs 3-4 words each. So the pointer advance cannot live in the loop
condition; it has to be a statement whose only cost is the branch delay slot.

Residue class for this body is now **definitively loop rotation**, with five spellings eliminated and
measured: pointer for, for with two breaks, do-while on the count, and both orderings of the
compound condition. The kept 25-word draft is the only form that is size exact.

## func_8001CAA8 — best stays 93/109, size exact

| # | shape | measurement |
|---|---|---|
| 0 | do-while outer + while inner (kept) | 93/109, 0x1b4 |
| 1 | drop the `end` local, inline `D_8008AE38 + D_8008AE3C` in both tests | 103/109, 0x1b8 |
| 2 | swap the outer walk's update order: `i++` before `tab += 0x10` | 101/109, 0x1b8 |
| 3 | swap the inner walk's update order: `j++` before `cur += 0x78` | 102/109, 0x1b8 |

All three regressed by a word and about ten words respectively, so the kept draft's `end` local and
update orders are the best measured combination. Residue: allocation inside the two walks plus one
saved-register home (the draft spends an extra `$s6` the game does not).

## State

Conversions 0, bodies attempted 2, shapes measured 5, PRs 0 (nothing matched).

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
Best drafts unchanged in `work/best/`.
