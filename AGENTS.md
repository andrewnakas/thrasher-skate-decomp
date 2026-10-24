# AGENTS.md: how to contribute (AI agents and humans alike)

This is the single source of truth for working in this repo. `knowledge.md` points here.
Read [RULES.md](RULES.md) and [PROVENANCE.md](PROVENANCE.md) once, and
[docs/MATCHING_GUIDE.md](docs/MATCHING_GUIDE.md) before your first function.

## What you are doing

You turn one function of `SLUS_009.35` from asm back into C that compiles to **exactly** the same
instructions under the pinned toolchain (gcc 2.8.1-psx + maspsx, `toolchain/compiler.toml`). One function per
file: `src/funcs/func_XXXXXXXX.c` (uppercase hex address). Nothing else is a contribution: the gates judge
only `src/funcs/` files.

## Lanes (so agents do not collide)

| Agent | Address range (game code) | Branch prefix |
|---|---|---|
| Codex | `0x80011B48`–`0x80034FFF` | `codex/` |
| Freebuff | `0x80035000`–`0x80058633` | `freebuff/` |
| Humans | anywhere, but claim first | anything |

`0x80058634` and above is Sony's PsyQ library: not a decomp target. Don't touch it.

Each agent should use **its own GitHub account**. Claims belong to accounts, so two agents on one account
defeat the claim system. The maintainer maps accounts run by one person in `steward.toml` `identities`.

## Setup (once per workspace)

```sh
git clone --recursive https://github.com/andrewnakas/thrasher-skate-decomp && cd thrasher-skate-decomp
# your own disc dump goes under disc/ (git-ignored)
python3 toolchain/setup.py
.venv/bin/python tools/extract_disc.py
.venv/bin/python tools/split.py
.venv/bin/python configure.py && .venv/bin/ninja        # must print SLUS_009.35: OK
```

Use **one clone per agent**. Never run `split.py`, `gate.py` and `build.py` at the same time in one clone:
they share `asm/`, `build/` and `build.ninja`. Keep parallel compiles low (`-j2` to `-j4`) when several agents
share one machine; RAM runs out before CPU does.

## The loop, per function

1. **Pick and claim.** `.venv/bin/python tools/new_func.py --next` lists small undone functions. Choose one in
   your lane and comment on the pinned **Active claims** issue: `/claim 0x80012345` (up to 3 open claims,
   0x2000 bytes each; claims lapse after 7 days without activity). Someone else's claim wins. Pick another.
2. **Draft.** `.venv/bin/python tools/new_func.py func_80012345` writes an m2c draft to
   `src/funcs/func_80012345.c` and runs a match.
3. **Iterate.** `.venv/bin/python tools/match.py func_80012345 --show` until it prints `MATCH`. Fix types,
   declare structs, reshape loops; see the matching guide. If it's close but not there, try per-file flags on
   the **first line**: `/* cflags: -mno-split-addresses */` (the allowed list is in `toolchain/compiler.toml`).
4. **Permute near misses.** `.venv/bin/python tools/permute.py func_80012345 --run -j2`. It refuses to start if
   its pipeline drifts from `match.py`'s. Apply only the meaningful change back to readable C, never permuter
   noise.
5. **Check locally, exactly as the judge will:**
   ```sh
   .venv/bin/python tools/scan.py && .venv/bin/python tools/gate.py && .venv/bin/python tools/build.py
   ```
6. **Give up cleanly.** After about 15 attempts on a small function, or 25 on a large one, delete the file,
   keep your near miss under `work/` (git-ignored) with a note on the remaining difference, `/unclaim`, and move
   on.
7. **Open a PR** from a branch with your lane prefix. Use the template, tick every provenance box that is true,
   tick exactly one "who made this" box, and agents also tick the acknowledgement. Up to 20 functions per PR.
   Steward judges it and merges it if everything passes. Read its comment if not: it lists `yours | game` for
   each differing instruction.

## Hard rules (the scan gate enforces most of them)

- **Plain C only.** No `asm`/`__asm__`, no register pinning (`register x asm("$s0")`), no `.set noreorder`,
  no `#pragma`, no `INCLUDE_ASM` in unit files. A match faked with asm is not a match.
- **No hard-coded RAM addresses** (`0x80010000`–`0x801FFFFF`). Use the symbol (`D_8008AEE4`, `func_8003B068`).
  Hardware registers and the scratchpad (`0x1F800000`…) are fine as constants.
- **One function per file**, named for its address. No helper functions, no `static` data, no initialised
  globals: data stays in the asm and is referenced with `extern`. String literals, jump tables (`switch`) and
  constants the function itself owned in the original are fine; the build places them correctly.
- **Never edit protected paths:** `tools/`, `config/`, `toolchain/`, `include/` (except `include/game/`),
  `tests/`, `configure.py`, `steward.toml`, `.github/`, or the docs. A PR touching them is escalated to the
  maintainer and not auto-merged. If the toolchain is wrong, open an issue labelled `tooling` with a minimal
  repro (a C file plus `match.py --show` output).
- **Shared types** go in `include/game/*.h`. A change there re-checks every merged unit, so a header edit that
  breaks an earlier match fails the gate.
- **No game data** in the repo: no disc images, no executable bytes, no assets.
- **Names need a reason.** Keep `func_`/`D_` names unless the binary itself shows the purpose (a debug string,
  a PsyQ signature, unmistakable behaviour). Never use names from leaked material.
- **No git surgery on others' work.** Don't edit another person's merged function without going through
  Steward's owner rule (it asks them; 7 days of silence means go ahead).

## Commands Steward understands (comment on the claims issue or a PR)

`/claim 0xADDR [SIZE]` · `/unclaim ID` · `/status` · `/next` · `/consent PR`

## Useful facts

- The game is C, built with Z-Axis's "zge" engine. Source file names survive in strings (for example
  `zge/zsndSeq.c`, `zge/psx/sound/psxchan.c`).
- `$gp` = `0x80089F18`; small globals (8 bytes or less) are gp-relative (`-G8`).
- Everything the game references by address is in `config/functions.us.csv`, `config/rodata.us.csv` and the
  splat output under `asm/`.

## Matching findings (each proved on a merged unit — apply before reading `work/` notes)

Triage first, then shapes. `match.py` reports `size 0xNNN, want 0xNNN`: if those differ the body is
missing/extra instructions, so no allocation shape will ever match — fix structure, don't permute.

- **Frame size before shape.** Compare your object size against the asm's declared size as soon as it compiles;
  a short/long body means a missing or duplicated instruction, not register allocation (`func_800358A8`,
  `func_80042338`).
- **≤8 bytes goes gp-relative** (`-G8`): a small `extern` yields `lw $x, %gp_rel(...)`, so when the game uses
  absolute `lui`/`%lo`, declare a bigger object and cast — `extern u8 D_8008B3A0[0x40]; *(u8 **) D_8008B3A0`
  (`func_8004912C`, `func_8004126C`).
- **Per-file cflags on line 1** — `/* cflags: -mno-split-addresses */` (allowed list:
  `toolchain/compiler.toml`). Required when the game materialises whole addresses up front rather than leaning
  on a split `%hi`/`%lo` base; it moved `func_8004912C` from `0xF8` to `0x100` in one step (`func_8003F964`).
- **`andi` on a parameter means the parameter is narrow**; a `u16` loop counter produces `andi`+`sltiu`, and
  `sltiu` wants a `u32` counter (`func_8003F000` group).
- **One statement per operation.** A separate scaled-offset statement, or a separate shift statement, decides
  which instruction gcc puts in a `jal` delay slot (`func_80050058`, `func_80053A4C`).
- **Check `.rodata` yourself: `match.py` cannot see it.** Read `asm/nonmatchings/game/jtbl_XXXXXXXX.s` for the
  real case order, and spell out an empty `case` — without it gcc emits a compare chain instead of the game's
  `sltiu`/`jr` table (`func_8004836C`).
- **Scheduler class — do not chase it.** A `jal` slot filled where the game leaves `nop`, or a load hoisted
  across a store, is a compiler decision, not a source shape; log it on issue #17 and move on
  (`func_80055820`, `func_8004E460`, `func_80042E9C`).
- **The permuter only pays on instruction-complete units.** It found nothing on `func_8003ED28` (complete, 5 of
  60, allocation-limited) after thousands of iterations, and cannot help a body with the wrong instruction
  count. The longest-lived near-misses here are 1-3 words of allocation residue.
