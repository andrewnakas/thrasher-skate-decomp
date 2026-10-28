# Pass: put the guard on main, then draft (29 Oct 2026)

## The guard is on main

`lane/select.py` + `lane/README.md`, PR [#196](https://github.com/andrewnakas/thrasher-skate-decomp/pull/196).
Not in `tools/` — that path is protected — and not in `work/`, which `.gitignore` excludes; `lane/` is a
new top-level directory for lane tooling, with no unit files touched.

Behaviour: `sync` fetches and cuts the working tree to `origin/main` in one command and refuses to finish
unless `HEAD` is that sha with no unit file differing; `list` never prints a merged body (it counts them);
`check` refuses a merged body, a missing listing, a dirty `src/funcs` or a drifted tree; `draft` runs
`check` first and refuses a merged body, an existing unit file, or a missing/unreadable draft source
without writing anything.

### Proved from a fresh checkout

`git worktree add /tmp/fresh-main origin/main`, with only the PR's two files materialised — no `asm/`,
no build tree, no `.venv`, system `python3`:

```
synced: HEAD = origin/main = 0e9a9f57, src/funcs clean, 675 units (no asm listings here: ...)
select: no asm/nonmatchings/game in this checkout — run tools/split.py first        (list, exit 1)
REFUSED func_8002FE80: MERGED on main@0e9a9f57 (src/funcs/func_8002FE80.c exists)   (check, exit 1)
OPEN func_80011B3C (unmerged at main@0e9a9f57; no listings in this checkout)         (check, exit 0)
REFUSED func_80011B3C: draft source /tmp/nope.c does not exist — nothing written    (draft, exit 1)
REFUSED func_8002FE80: MERGED on main@0e9a9f57 — nothing drafted                    (draft, exit 1)
drafted src/funcs/func_80011B3C.c (main@0e9a9f57)
select: not measured — no asm listings in this checkout                             (draft, exit 0)
select: src/funcs has local edits, selection would be unsound: M ...                (check, exit 1)
```

### Two defects found while landing it

- The sync stamp was written to `lane/.select-sha`, which does not exist on a branch that has no `lane/`
  — `sync` died on the first use from a main-based tree. State now lives in the git dir
  (`$(git rev-parse --git-dir)/lane-select-sha`), which survives every branch switch.
- `sync` cut the tree to `origin/main` and so deleted the unmerged tool it was being run from. It now
  accepts a tree that is `origin/main` **plus `lane/` only**, and still cuts anything else.

### Did it survive a branch switch without manual restoration?

Yes. `lane/` is a tracked file on its branch; `git checkout freebuff/lane-select` restores it with the
tree, `git checkout -B <branch> origin/main` removes it while the PR is unmerged, and switching back
brings it back with no manual copying. It vanished once more this pass only because `sync` cut to main
*before* the fix above — after the fix, both sync and the tool survive. Once #196 merges it is on every
main-based branch by construction.

## Drafting: 1 conversion found, 0 shippable

| function | words | result |
|---|---|---|
| func_800382C0 | 12 | park — allocation. Turns on `srl $v0,$v0,7`: the game keeps the whole accumulator in `$v0` (and `addu $v0,$a0,$v0` folds the parameter back in), ours accumulates in `$v1` and copies to `$v0` in the return path. 8 of 12 after the assign-to-result rewrite; the ternary form is worse (11 of 12). |
| func_80034B98 | 16 | **MATCH**, not shippable — see below. Two changes: the value loaded from `D_800843E8` is the argument to `func_80034BD8` (the argument rule again — that is what puts it in `$a0`), and `-mno-split-addresses` makes the load `lui $a0,%hi; lw $a0,%lo($a0)` instead of going through a temporary. |

### The block

`func_80034B98` stores `0x801FC000` into `D_8008B0F4`. `tools/scan.py` refuses the literal ("hard-coded
address 0x801FC000: reference the symbol (D_801FC000) instead"), and **no symbol exists at or above
0x801F0000** in `config/symbol_addrs.us.txt`, `config/functions.us.csv` or the splat output — the only
occurrence of that address in the tree is this listing. Declaring `extern u8 D_801FC000[];` links
against nothing and the build fails. Adding the symbol means editing `config/`, which is protected.

So the body is converted as C and blocked by configuration, not by source shape: a body that
materialises a RAM address above the splatted data region cannot be written under the current scan rule.
Worth a `config/`-side fix (or a scan exemption for absolute addresses in a unit that cannot name them).

## Queue

`origin/main` at `ebba874e` (676 units, PR #195 landed): **676 merged, 406 unmatched listings open.**
