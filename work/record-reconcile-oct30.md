# pass oct30 — reconcile the attempted set, two fresh drafts

## The bookkeeping defect, and the step that caused it

The records branch never drops an entry: a body that merges upstream keeps its `work/best/*.c` and its
lines in `work/*.md` forever, and every later pass read that as open work. Nothing compared the
records against upstream, so the only defence was the author remembering to check — which is exactly
what failed last pass, when `func_8001D804` and `func_8002FE80` were drafted from `work/best` before
anyone noticed both were merged.

**Recomputed against `origin/main` = `f41520e5` (687 units): 344 recorded entries, 96 of them now
merged — 28% of the attempted set was stale.** That is the number of entries whose status changed.

The fix lives where staleness is created: `lane/select.py sync` now calls `reconcile()` after the tree
is pinned to upstream and publishes `work/attempts.tsv`:

    body            status  best    source
    func_80011B48   merged  12/17   work/band-oct28/func_80011B48.c
    func_80011B3C   open    unrecorded  work/record-clamp-bench-oct28h.md

and prints how many entries are now merged, how many status changes, new and dropped. `list` prints
`96 recorded-but-merged` beside the open count, so the published record and the selector's refusal
agree by construction — `check func_8001D804` says `REFUSED … MERGED` in the same run that the table
says `merged`. `reconcile` is idempotent: a second sync reports `0 now merged, 0 status changes`.

## Fresh drafts, address written in the refined form from the start

| body | words | measurement | residue / park |
|---|---|---|---|
| `func_8003012C` | 124 | 120/124, size 0x1f8 vs 0x1f0 | the table address is index-first (`*(u8 *)p * 8 + D_8006F890`), but gcc homes the base in `$v0` and the index in `$v1` where the game does the reverse, so the `addu` accumulates the base — the filed register-home class. Turn-on: none (allocation) |
| `func_8004ADA4` | 119 | 96/119, size 0x1d8 vs 0x1dc | ring-slot allocator drafted whole; both indexed addresses (`idx * 0x48 + D_800AEAA4`, `idx * 4 + D_800AEA24`) are index-first and land; the one-word gap is the entry copy `t1 = a0; s2 = t1` the game makes, which our `s2 = a0` does not — register home again |

Neither converted. Both are fresh ground now recorded, with the exact register their residue lives in.

## State

**Conversions 0, bodies attempted 2** this pass (two more reconciled as already merged). Pipeline:
scan 687 files 0 problems, gate pass, build `SLUS_009.35: OK`, tree `f41520e5`, 687 local = 687
upstream.

## Where the fix lives

`lane/select.py` is tracked on `main`, so the reconcile code is a worktree change here, not a shipped
unit. It is committed to the records branch as `lane/select.py` alongside `work/attempts.tsv` so it
cannot be lost if the worktree is reset; landing it on `main` is a maintainer call, since this lane's
PRs are unit-file-only. Until then, any pass that runs `select.py sync` from this checkout gets the
reconcile; a pass from a fresh clone gets the refusal but not the published table.
