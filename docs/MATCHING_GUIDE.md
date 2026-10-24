# Matching guide (gcc 2.8.1-psx + maspsx)

Practical idioms for getting `tools/match.py` to say `MATCH`. Most come from the THPS N64 decomp, which used
the same gcc 2.8.1 back end; the PS1-specific parts are marked. Add to this file (maintainers) when a new trick
works more than once.

## Reading the diff

`tools/match.py func_X --show` prints `game | yours` per instruction, `!!` where they differ, and every
relocation resolved to the address it points at (`[gprel D_8008AC84 -> 0x8008AC84]`). A jump to the wrong
label or a load from the wrong table is a real difference: nothing is masked.

## PS1 / this game

- **No FPU.** `float` math compiles to libgcc soft-float calls (`__addsf3` and friends). Most game math is
  fixed-point integers; if you see shifts by 12, think `ONE = 4096` (PsyQ fixed point).
- **GTE** (geometry coprocessor) code uses `cop2`/`mtc2`/`lwc2` instructions. It came from PsyQ's inline GTE
  macros, which compile to asm. A function full of GTE ops cannot be written in plain C under our rules. Leave
  it for later (a tooling decision is pending).
- **Small data is gp-relative** (`-G8`): `lw $v0, %gp_rel(D_x)($gp)`. Declare the extern with its real size
  (`extern s32 D_x;`, or `extern s32 D_x[2];` for a two-element array). If the game uses `lui`/`addiu` (or an
  `$at` store) for a symbol near gp, the object is bigger than 8 bytes, or that file used different settings.
- **`lui $at` stores** (`lui $at, %hi(D_x); sb $v0, %lo(D_x)($at)`) come from the assembler's macro expansion.
  gcc 2.8.1 splits addresses itself by default (`lui $v1 ... sb $v0, %lo($v1)`). Files that show `$at` stores
  were built with `/* cflags: -mno-split-addresses */` (func_80011BD4, func_80011C40).
- **Address of a big object in two registers** (`lui $v0; addiu $t1, $v0, %lo(D_x)`) is gcc's own split:
  default flags.
- **Division** expands with `break 7` and overflow checks (`--expand-div`). Write a plain `/`.
- **Epilogue:** gcc 2.8.1 fills the `jr $ra` delay slot with the stack restore. If the game leaves `nop` there,
  look for a different statement order first, not different flags.

## Types and declarations

- Unknown struct? Declare a local one with padding: `typedef struct { u8 pad[0x24]; s16 unk24; } Foo;`. When two
  functions agree on a layout, move it to `include/game/` (shared, unprotected; changes re-check every unit).
- `s16`/`u8` parameters cause `sll/sra` or `andi` at first use; the game's choice tells you the type.
- A call that leaves an argument register untouched: declare the callee with fewer parameters.
- The game copies `$s0` to `$v0` and stores through it: the previous call **returns** that pointer.
- Constructors returning `this` ($v0 = $a0 throughout): end with `return arg0;`.
- An unexplained copy into `$v0` at the end: the function returns that value.
- Globals the game reloads every time: `extern volatile`.

## Control flow

- Switch case order sets the order of the case blocks; a `switch` makes the jump table (owned rodata is fine).
- Top-tested loop with a `j` back: `i = 0; while (1) { if (i >= n) break; ...; i++; }`.
- Down-counting loops can be gcc reversing a plain `for`: give each loop its own block-scoped counter.
- Retry loops: `r = f(); while (1) { if (r != 2) break; g(); r = f(); }` lets gcc merge the calls.
- Two calls differing in one argument: an if/else lets gcc merge them into the game's branch shape.
- Cross-jumping merges identical tails. When the game keeps them separate, flip the if/else polarity of each copy.
- Funnel every `continue` through one `goto next; ... next: i++;` to change s-register priority.

## Register allocation and scheduling

- Wrap statements in `do { ... } while (0);`: a cheap first sweep that fixes many near misses.
- Reordering local declarations changes stack/spill slot order. One variable per block fixes register order.
- A fresh variable instead of overwriting a parameter, or reusing a temp in place (`t *= t`).
- Evaluation order: precompute a call argument into a local, or cache a global in a local at entry.
- Re-reading a field instead of caching it often fixes an unfilled delay slot.
- gcc folds or reorders a constant: put it in a local at entry (`mask = ~1;`).
- Base/index swapped: use an explicit element pointer (`E *e = &a[i];`).
- `arr[i].field` instead of pointer stepping moves the loop's address setup.
- `&local` passed to calls: wrap each such call in its own `{ }` to control stack-slot reuse.
- Scalar locals instead of an array/struct change alias analysis (loads hoisted, exit tests duplicated).
- Declare an argument as a struct with named fields instead of `*(T *)((u8 *)p + off)` casts; gcc then
  treats globals and fields as non-aliasing and schedules like the game.

## Flags

The game mixes settings per source file. Try them on the first line only, from the allowed list:
`/* cflags: -mno-split-addresses */`, `-O1`, `-O3`, `-fno-schedule-insns`, `-fno-schedule-insns2`,
`-fno-strength-reduce`, `-G0`, `-G4`, `-funsigned-char`. Functions that sit next to each other usually share a
source file and so share flags: check the neighbours' units.

## When to stop

About 15 attempts for a small function, 25 for a big one. Then run the permuter (`tools/permute.py`), apply
only a change that reads like real code, and if that fails, move on. Keep your best near miss in `work/` with
a note on the remaining difference.
