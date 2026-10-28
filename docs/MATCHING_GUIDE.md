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
- **Scalar extern vs array extern decides gp-relative or absolute.** A scalar `extern s32 D_x;` has an unknown
  size, so the assembler treats it as small data and emits `lw $v0, %gp_rel(D_x)($gp)` even where the game uses
  `lui`/`lw`. Declaring it as an **unsized array** (`extern u8 D_x[];`, then `*(s32 *) D_x` or
  `*(s32 *)(D_x + off)`) makes it a big object and restores the absolute `lui`/`lo` form. func_800494A4 turned on
  exactly this: the scalar form shifted every word by the missing `lui` at three load sites (0x74 vs 0x80 bytes).
- **The mechanism is the object's size against `-G8`, not its type name.** A `u8`, a `u8[4]`, an `s32[2]` and a
  pointer are all <= 8 bytes and all go through `$gp`; any declaration whose size exceeds 8 bytes is addressed
  absolutely. So to reproduce a `lui $v0, %hi(D_x)` + `lbu $v0, %lo(D_x)($v0)` pair from a one-byte symbol,
  declare it as an aggregate just over the threshold (`extern u8 D_x[16];`, read `D_x[0]`). That one edit took
  func_80055820 from 27 to 1 of 34 words. Two caveats, both measured: (1) it only works where the draft *reads
  or writes the value* — if it takes the symbol's **address** (`p = D_x;`, `&D_x`), resizing silently turns the
  address into an element load and the score moves for the wrong reason; (2) a symbol that is read once and
  written once at the end of the body can still be pinned in a callee-saved register, which costs a saved word
  (func_80038970, func_80043294 6 -> 15). `work/gp_sweep.py` mechanises the check over every drafted body and
  labels the address-use cases as shape probes.
- **A symbol `lui` that the game re-emits at each use**: gcc hoists it into one register (sometimes a
  callee-saved one) when the address outlives a call. `/* cflags: -mno-split-addresses */` stops the hoist and
  took func_800494A4 from 24 differing words to 9. It also changes block-move addressing, so re-check copy
  loops in the same unit (func_80056C90 went from 2 to 31 differing words with it on).
- **Global table base before the index**: when the listing builds `lui`/`addiu` for the table *first* and the
  index arithmetic after, keep a hoisted base pointer (`base = Table; e = &base[i];`) instead of `&Table[i]`,
  which folds the base into the store address. func_80035BC0 closed on that spelling.
- **A constant offset that lands in the store** (`sh $a3, 0x20($a0)` instead of `addiu` then `addu`): give the
  offset its own local (`off = i * 6 + 0x20; p = (T *)(base + off);`). func_8003571C matched as soon as the
  index literal stopped folding into the base.
- **Division** expands with `break 7` and overflow checks (`--expand-div`). Write a plain `/`.
- **Epilogue:** gcc 2.8.1 fills the `jr $ra` delay slot with the stack restore. If the game leaves `nop` there,
  look for a different statement order first, not different flags.

## Types and declarations

- Unknown struct? Declare a local one with padding: `typedef struct { u8 pad[0x24]; s16 unk24; } Foo;`. When two
  functions agree on a layout, move it to `include/game/` (shared, unprotected; changes re-check every unit).
- `s16`/`u8` parameters cause `sll/sra` or `andi` at first use; the game's choice tells you the type.
- A redundant `andi $v0, $v0, 0xFF` right after an `lbu` means the source promoted a `u8` **local** (or
  parameter): declare the temporary `u8`, not `u16`, or gcc folds the mask away. func_80035BC0 needed both
  bytes as `u8` locals to keep the two masks.
- A store of `0xFF` that the game materialises as `-1` (`addiu $r, $zero, -1` then `sb`) means the field is
  **signed**: declare it `s8` and write `-1`. With a `u8` field the same source materialses `0xFF`, and the
  word differs even though the byte stored is identical (func_80034DE8, 43 -> 41 of 67 words on that one
  change).
- A `nor` chain often means a bitwise-not of a promoted pair; the order of the operands decides where the two
  masks land (`(b | (a << 8))` versus `((a << 8) | b)` — the second-order spelling was worth 5 words in
  func_80035BC0).
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
- A `la` whose `lui` lands in a different register than the `addiu` target (`lui $v1; addiu $t0, $v1, %lo`
  where the game has both in one register) is allocation, not typing: try a struct-typed object instead of an
  array, or a bigger object type, before spending more attempts (func_80056C90 sat at 2 of 36 words on it).
- An unaligned 8-byte copy (`lwl`/`lwr` pairs) is gcc's block move for an alignment-1 struct: declare
  `typedef struct { u8 b[8]; }` and assign through it. A 16-byte-chunked `lw`/`sw` loop with a 12-byte tail is
  the same move for a `u32`-aligned struct whose size is not a multiple of 16 (func_80056C90).
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

## Levers measured but not yet in a shipped unit

Each of these was measured on a near miss in `work/`; the number is the score it produced there.

- **A dispatch arm that legitimately does nothing must be left empty.** `nudge = 0;` makes gcc
  re-materialise the zero and re-thread the chain (21 words, func_80038610); the empty arm gives the
  game's `bnez $v0, tail` (13).
- **A byte-swapped value wants `u32`, not `u16`.** With `u16` the `andi $v0, $v1, 0xFFFF` lands
  *before* the shifts; with `u32` it survives only at the return and `srl` (not `sra`) falls out.
- **`(v >> 8) & 0xFF | (v << 8)` is the game's operand order** for a halfword swap; reversing the
  two terms moves the `or` destination register.
- **Declaration order does not steer `$s`-register rank.** Three orders on func_800250B4 all gave
  86/173 words, and three orders on the two cursors of func_8001C540 all gave 14/59 with an
  otherwise identical instruction stream. When two saved registers hold swapped roles, changing the
  spelling will not move it; that is an allocation tie, and it needs a permuter or a tooling
  decision, not another attempt.
