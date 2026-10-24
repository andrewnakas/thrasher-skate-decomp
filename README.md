# Thrasher: Skate and Destroy (PS1) decompilation

![Code](https://bytematch.dev/andrewnakas/thrasher-skate-decomp.svg?label=Code&measure=matched_code_percent)
![Functions](https://bytematch.dev/andrewnakas/thrasher-skate-decomp.svg?label=Functions&measure=matched_functions)

A matching decompilation of **Thrasher: Skate and Destroy** (Z-Axis / Rockstar Games, 1999, PlayStation,
NTSC-U `SLUS-00935`). The game's C is being written back function by function until it compiles to the
original executable byte for byte.

**Bring your own disc.** This repository contains no game code or data. You need your own legally
owned copy of the game, dumped yourself, to build or check anything.

## Status

| | |
|---|---|
| Target | `SLUS_009.35` (sha1 `16829afba66533e2645bf87af2774671b06ff36b`), loaded at `0x80010000` |
| Compiler | PsyQ-era **gcc 2.8.1** (`cc1psx`), `-O2 -G8`, with [maspsx](https://github.com/mkst/maspsx) standing in for ASPSX (pinned in `toolchain/compiler.toml`) |
| SDK | PsyQ 4.4 libraries (identified by signature; they stay asm) |
| Split | 1081 game functions (289 KB) + 417 PsyQ library functions, via [splat](https://github.com/ethteck/splat) |
| Build | The full executable rebuilds byte-identical from C + asm |

Progress is tracked on [bytematch.dev](https://bytematch.dev/andrewnakas/thrasher-skate-decomp).

**Joining (human or AI agent)? Read [START_HERE.md](START_HERE.md).** It goes from a fresh machine to a
first PR, and includes a prompt to paste into your agent.

## Quick start (Linux, no root needed)

```sh
git clone --recursive https://github.com/andrewnakas/thrasher-skate-decomp
cd thrasher-skate-decomp
# put your disc dump (the .bin/.cue, a single MODE2/2352 track) anywhere under disc/
python3 toolchain/setup.py          # pinned compiler, binutils, objdiff, m2c, permuter, .venv
.venv/bin/python tools/extract_disc.py   # verifies the disc and extracts SLUS_009.35
.venv/bin/python tools/split.py          # splat: asm/ and the function table
.venv/bin/python configure.py && .venv/bin/ninja   # -> SLUS_009.35: OK
```

Or use the container: `docker build -t thrasher . && docker run --rm -v $PWD:/src thrasher`.

## Working on a function

```sh
.venv/bin/python tools/new_func.py --next            # small functions nobody has done yet
.venv/bin/python tools/new_func.py func_80012345     # m2c draft -> src/funcs/func_80012345.c
.venv/bin/python tools/match.py func_80012345 --show # side by side, !! marks differences
.venv/bin/python tools/permute.py func_80012345 --run -j4   # near misses: decomp-permuter
.venv/bin/python tools/decompme.py func_80012345     # files + flags for a decomp.me scratch
.venv/bin/python tools/scan.py && .venv/bin/python tools/gate.py && .venv/bin/python tools/build.py
```

Then open a pull request using the template. Claim first: comment `/claim 0x80012345` on the pinned
**Active claims** issue. See [AGENTS.md](AGENTS.md) for the full workflow, which applies to humans too,
[RULES.md](RULES.md), [PROVENANCE.md](PROVENANCE.md) and [docs/MATCHING_GUIDE.md](docs/MATCHING_GUIDE.md).

## How merges work

[Decompathon Steward](https://github.com/andrewnakas/decompathon-steward) runs on the maintainer's machine,
which has the disc. **No AI is involved in merging.** For every PR, Steward checks out `main`, copies in only
the PR's `src/funcs/` files, and runs five deterministic gates:

| Gate | Tool | Checks |
|---|---|---|
| toolcheck | `tools/toolcheck.py` | the toolchain is the pinned one (sha256 + canary compile) |
| scan | `tools/scan.py` | plain C only: no inline asm, register pinning, `#pragma`, hard-coded addresses |
| split | `tools/check_split.py` | the split is sound and deterministic |
| match | `tools/gate.py` | every unit matches instruction for instruction, defines one function, owns no data, and no earlier match regresses |
| build | `tools/build.py` | the whole executable is byte-identical (sha1), and objdiff independently agrees |

If every gate passes and the policy rules (claims, provenance boxes, size) are satisfied, Steward merges.
Otherwise it labels the PR and posts a comment with a yours-vs-game table. Public CI (GitHub Actions)
runs the checks that need no disc: lint, scan, tests, and a compile of every unit.

## Layout

```
config/       splat yaml, symbol files, function + rodata tables, checksums
src/funcs/    one matched function per file: func_XXXXXXXX.c
include/      common.h, PsyQ headers; include/game/ for shared game types
tools/        the build and every gate (see the table above)
toolchain/    compiler.toml (the pinned pipeline), setup.py, maspsx submodule
configure.py  writes build.ninja + the link script (every object pinned to its address)
```

## Credits

Built on [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm),
[maspsx](https://github.com/mkst/maspsx), [decompals/old-gcc](https://github.com/decompals/old-gcc),
[m2c](https://github.com/matt-kempster/m2c), [decomp-permuter](https://github.com/simonlindholm/decomp-permuter),
[objdiff](https://github.com/encounter/objdiff) and
[psx_psyq_signatures](https://github.com/lab313ru/psx_psyq_signatures). The project structure follows the
[THPS N64 decomp](https://github.com/andrewnakas/thps64).

The code in this repository is released under CC0 (see [LICENSE](LICENSE)). Thrasher: Skate and Destroy
is © its respective owners; this project is not affiliated with or endorsed by them.
