# Status / engineering log

## 2026-10-24: project bootstrapped

**Disc.** USA single-track MODE2/2352 dump; `SYSTEM.CNF` boots `cdrom:\slus_009.35;1`. 62 files, checksums in
`config/checksums.us.sha1`. `SLUS_009.35` is 0x7B000 bytes loaded at 0x80010000, entry 0x8005D1B0,
`$gp` = 0x80089F18. A second executable, `PLAYMOV.EXE` (FMV player, loads at 0x80160000), is not a target yet.
Game data is in `ASSETS/*.ZAL`, audio in `AUDIO/*.ZSD`, movies in `MOVIE/*.STR` (XA form 2).

**SDK.** `tools/psyq_identify.py` matched 152 PsyQ 4.4 library objects (more than any other version) and named
170 library functions (`config/psyq_syms.us.txt`). The libraries start at `memset` = 0x80058634; everything
from 0x80011B48 up to there is game code (the "zge" engine plus the game). Source names survive in strings:
`zge/zsndSeq.c`, `zge/zsndAnnc.c`, `zge/zsndSrc.c`, `zge/psx/sound/psx{chan,load,smus,Strm}.c`.

**Split.** splat 0.50.0: 1081 game functions (289,476 bytes), 417 PsyQ functions, 153 standalone rodata
pieces (134 used by exactly one function). The all-asm build reproduces `SLUS_009.35` byte for byte.

### Compiler identification

Candidates: decompals/old-gcc 0.17 `gcc-2.6.3-psx`, `2.7.2-psx`, `2.7.2-cdk`, `2.8.0-psx`, `2.8.1-psx`, each with
maspsx `--aspsx-version` 2.56 / 2.67 / 2.77 / 2.79 / 2.86, `-G0` and `-G8`. Decided by hand-written functions:

| Function | What it shows | Matches |
|---|---|---|
| func_80011B8C, func_80011C9C, func_80011D34 | gcc fills the `jr $ra` delay slot with the stack restore | 2.8.0, 2.8.1 only |
| func_80011CBC | struct copy; address built in two registers (gcc's own split) | 2.8.x only |
| func_800204F4, func_80024D50, func_80037DAC | explicit `%gp_rel` for small arrays, gp-relative `la` | 2.8.1 only (all ASPSX versions) |
| func_80011BD4, func_80011C40 | `lui $at` stores (assembler macro expansion) | 2.8.1 with `-mno-split-addresses` (or 2.6/2.7) |
| func_80016204 | string literal in the function's own rodata | 2.8.1 |
| func_800383E8 | `switch` with its own jump table | 2.8.1 |

Result: **gcc 2.8.1-psx, `-O2 -G8`**, maspsx `-G8 --expand-div` (division expands with `break 7` checks).
`-mno-split-addresses` is a per-file flag (the 0x80011B48..0x80011C9C file uses it). The ASPSX version is
tentative (2.67): nothing seen so far distinguishes 2.56 to 2.86 under gcc 2.8.1, which emits explicit
relocations. Revisit if a function does.

Open: func_80011B48 (the RNG) is 2 instructions off (the order of `srl`/`sll` in the 16-bit rotate) under
every compiler. It's a source-shape question; a good first permuter target.

### Seed matches (11)

func_80011B8C, func_80011BD4, func_80011C40, func_80011C9C, func_80011CBC, func_80011D34, func_80016204,
func_800204F4, func_80024D50, func_80037DAC, func_800383E8. The full build with these in C is byte-identical, and
objdiff independently reports all 11 at 100%.

### Pending tooling

- GTE: functions that use the geometry coprocessor need PsyQ's GTE macros (`gtemac.h`/`inline_c.h`
  equivalents) in a protected header under `include/psyq/`, so units call macros and contain no asm.
- PsyQ headers (`libgpu.h`, `libgte.h`, `libetc.h`, …) for prototypes and structs, as functions need them.
