# Start here: joining the Thrasher decomp (agents and humans)

One page to go from a fresh machine to your first merged function. The details live in
[AGENTS.md](AGENTS.md); read it before your first PR.

## What you need

1. **Linux** (or WSL2, or Docker), Python 3.11+, git, `gh` logged in, and about 2 GB of free disk.
2. **Your own dump of the game**: Thrasher: Skate and Destroy (USA), `SLUS-00935`, as a single-track
   `.bin`/`.cue` (MODE2/2352). The repo contains no game data and nobody will send you any. The tools verify the
   dump by checksum, so a wrong region or a bad dump fails at once.
3. **Your own GitHub account.** Claims belong to accounts, so two agents sharing one account step on each other.

## Setup (about 5 minutes)

```sh
git clone --recursive https://github.com/andrewnakas/thrasher-skate-decomp
cd thrasher-skate-decomp
mkdir -p disc && cp /path/to/your/dump.bin disc/        # git-ignored, never committed
python3 toolchain/setup.py                  # pinned compiler, binutils, objdiff, m2c, permuter (no root)
.venv/bin/python tools/extract_disc.py      # must end with: OK: 62 files match
.venv/bin/python tools/split.py
.venv/bin/python configure.py && .venv/bin/ninja   # must end with: SLUS_009.35: OK
```

If any step fails, open an issue with the "Build or setup problem" template. Never attach game files.

## Your first function

1. Look at the pinned [Active claims](https://github.com/andrewnakas/thrasher-skate-decomp/issues/1) issue and
   pick an address range **nobody holds**. `.venv/bin/python tools/new_func.py --next` lists small undone
   functions. Claim it by commenting on that issue: `/claim 0x8004A000 0x800`.
2. Follow the loop in [AGENTS.md](AGENTS.md#the-loop-per-function): `new_func.py` → `match.py --show` → fix the C
   → `scan.py`, `gate.py`, `build.py` all pass.
3. Open a PR from a branch (`<your-agent>/...`), fill in the template, tick the provenance boxes that are true,
   and tick exactly one "who made this" box (agents also tick the acknowledgement). At most 20 functions per PR.

**Your first PR waits for the maintainer.** Steward runs the gates for a new account only after the maintainer
adds the `judge-ok` label, and a human merges that first PR. After one merged PR, everything is automatic:
Steward judges and merges as soon as the gates pass.

## Paste this to your agent (Freebuff, Codex, …)

> You are contributing to a matching decompilation at https://github.com/andrewnakas/thrasher-skate-decomp.
> Read START_HERE.md, then AGENTS.md, then docs/MATCHING_GUIDE.md, and follow them exactly. Set up the repo
> as START_HERE.md says (my disc dump is at `<PATH TO .bin>`) and confirm the build prints
> `SLUS_009.35: OK`. Then work continuously: read the pinned Active claims issue (#1), claim an unclaimed
> address range with `/claim`, match functions one at a time with tools/new_func.py and tools/match.py,
> check each with tools/scan.py, tools/gate.py and tools/build.py, and open PRs of up to 20 matched
> functions using the PR template, ticking every provenance box only after checking it against the PR.
> Plain C only: no inline asm, no register pinning, no hard-coded addresses, no edits outside src/funcs/
> (plus include/game/ for shared types). If a function doesn't match after about 15 attempts, drop it,
> note why in work/, and move on. If you think the tooling is wrong, open a `tooling` issue instead of
> working around it.
