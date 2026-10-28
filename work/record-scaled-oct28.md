# Pass: selecting on the offset-left lever (28 Oct)

Queue unchanged: fresh `origin/main` 7e24509, 663 merged, **354** unmatched.
Attempted **2** bodies (the target was five), converted **0**.

## The population

`work/enumerate.py --scaled` returns **200** unmatched bodies whose listing scales an index into a
base. Of those, **126 are undrafted**, and the *smallest undrafted member is 71 words* — every
small scaled body has been drafted already. So the lever's natural hunting ground (small bodies whose
only residue is an address build) is empty, and what is left is the framed 71-140 word band where an
address build is one difference among twenty.

## Attempts

| body | words | best | residue |
|---|---|---|---|
| func_8002C284 (retry with the lever applied *first*) | 71 | 20/71, size exact | no change from the same 20 — the index build `tbl[idx]` was already right; the residue is **cross-jumping** of the two identical recursive tails |
| func_8002AC14 | 86 | 80/86, 0x150 vs 0x158 | first transcription was structurally wrong at the entry (channel extraction hoisted above the guard); fixing that took it 84 -> 80. Remaining gap is the inner mixing loop's output-record recomputation — a second structural pass, not a residue |

## The lever's measured hit rate

| population | bodies tried | matches |
|---|---|---|
| parks at 1-6 words whose residue is an address build | 3 (func_8001DB74 2->0, func_80056C90, func_80056FF4) | **1** (and that one was already merged — stale park) |
| fresh undrafted scaled bodies at 71+ words | 2 (func_8002C284, func_8002AC14) | **0** |

The lever is real and cheap *when the address build is the only difference*. On fresh 71+ word
bodies it changes nothing, because the address is already correct in a first transcription and the
residue is elsewhere (cross-jumping, loop form, save order). That is the honest measurement: the
lever's hit rate falls to zero exactly where the remaining queue lives.

## Count

2 attempted, 0 converted. Queue 354. Best draft `work/best/func_8002AC14-s1.c`.
