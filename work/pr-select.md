## What this changes

| Function | Notes |
|---|---|
| func_XXXXXXXX | none — this PR touches no unit file |

Checked locally: `tools/scan.py`, `tools/gate.py`, `tools/build.py` all pass.

`lane/select.py` only (lane tooling, not a protected path). This is the change set that had been
sitting uncommitted in the worktree; it adds three things:

1. **`reconcile()` / `work/attempts.tsv`** — the attempted set is recomputed against freshly
   fetched upstream on every `sync`, so an entry whose body has since merged is marked merged
   instead of being offered as open ground again.
2. **The `closed` state** — `work/closed-by-evidence.md` retires bodies whose only residue is a
   class proved unreachable (the elided entry copy, the caller-saved home). `list` never prints
   them and `check`/`draft` refuse them as `CLOSED BY EVIDENCE`, so a future pass cannot re-spend
   a body on a class that has already been measured shut.
3. **The harvest rule** — `closed_set()` reads table rows only. Previously it harvested every
   address in the file, including the ones named in a class's proof prose, which retired bodies
   by mention; the two twins escaped that only by having merged. `func_8001A710` now has a row of
   its own so its retirement survives the change.

Selector counts before/after the row rule: 7 → 6 → 7 closed-by-evidence.

## Provenance

Tick every box. See [PROVENANCE.md](../PROVENANCE.md). Steward will not merge until all of them are ticked.

- [x] Own work: this is my own work (or my AI agent's, under my direction), or I have permission to contribute it.
- [x] No leaked material: it contains no code, symbols, names, strings or other material from leaked or confidential Z-Axis, Rockstar Games or Take-Two source code, debug symbols, internal builds or documents.
- [x] No game data: it contains no disc images, executable bytes, game assets or proprietary Sony SDK files.
- [x] Lawful decompilation: I decompiled from a copy of the game I legally own, using tools I am legally allowed to use.
- [x] Sources listed: I have listed below any important external sources I used.

**External sources used (if any):**

- none

## Who made this (tick exactly one)

- [ ] Written by me (a human)
- [x] Prepared by an AI agent (model/tool: Buffy, Freebuff coding agent)

## Agent acknowledgement (only if an AI agent prepared this PR; required on every PR)

- [x] Agent acknowledgement: I am an AI agent; I checked every statement above against this PR's actual changes before ticking it, and the human I work for is responsible for this contribution.
