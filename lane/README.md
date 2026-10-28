# lane/: tooling for a decomp pass

`select.py` is the guarded selection tool. It exists because this lane made the same class of mistake
twice, and both cost real work:

- drafting bodies that were **already merged** upstream, because the candidate list came from a tree cut
  before the merge (a third of one pass);
- drafting bodies that were **already attempted and parked**, because `work/` is gitignored and the parks
  live on the records branch — a main-based tree cannot see them (`func_8002AC14` was transcribed from
  scratch in the pass of 2026-10-28c while an earlier record held it at 81/86).

Every pass starts here:

```sh
python lane/select.py sync                    # fetch, cut the tree to origin/main, record the sha
python lane/select.py list --max 40           # open bodies, ascending size, each tagged
python lane/select.py list --min 70 --fresh   # never-attempted bodies only
python lane/select.py check func_80012345
python lane/select.py draft func_80012345 --src /tmp/body.c
```

## Three states, not two

`list` and `check` classify every open body:

| state | meaning | what the tool does |
|---|---|---|
| `merged` | `src/funcs/<name>.c` exists on main | never printed, never drafted |
| `attempted` | a path under `work/` on the records branch names it | printed with its best recorded residue; `check` and `draft` refuse it when the intent is fresh ground |
| `fresh` | neither | the only state `list --fresh` prints |

Attempt state is read from the records branch, not the working tree: `sync` fetches, and
`records_ref()` takes the newest `origin/*/records-*` branch (override with `--records REF` or
`LANE_RECORDS_REF`). A file name is enough to prove an attempt; inside a markdown record a line counts
only if it also carries evidence — a `work/` path, an `N/M` residue, or a `not C` verdict — so a queue
census row that merely lists a body as open does not mark the whole project attempted.

`draft --allow-attempted` is the escape hatch for deliberately re-testing a park, and the pass then has
to say so in its record.

## The merge guard

`sync` fetches and cuts the working tree in one command and refuses to finish unless `HEAD` is exactly
`origin/main` (or `origin/main` plus unmerged `lane/` tooling) and no unit file differs from it.
`check`, `list` and `draft` re-validate that state, so a body cannot be drafted from a tree that has
drifted; `draft` refuses a merged body, an existing unit file, or a missing draft source, and never
removes a file.

A checkout needs `asm/nonmatchings/game/` (`tools/split.py`) for body sizes and for `list`. Without it,
`sync`, `check` and `draft` still work — `check` reports the merge/attempt state alone, and `draft` says
it could not measure. `draft` then runs `tools/match.py`, which needs a full build tree.

This directory is not `tools/`: `tools/` is the repository's own toolchain and stays untouched by lane
work.

## The worktree assertion

Branch gymnastics dropped a merged unit file from the worktree once and it had to be restored by
hand. `verify` compares `src/funcs` against `origin/main` in both directions and names anything that
went missing or was edited in place:

```sh
python lane/select.py verify                 # 676 unit files, every merged body present and unedited
```

`sync` and `draft` call the same assertion, so a tree that lost a merged unit cannot be used to
choose or start a body. Untracked drafts are expected and are not a problem; a missing or modified
merged file is a refusal.
