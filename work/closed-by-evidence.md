# Closed by evidence — classes that must not be re-tested

Two register classes are now proved by measurement rather than assumed. A body whose *only* residue
is one of these is closed here and must not be drafted again; a body with one of these **plus** other
words is still open on those other words.

## A. Elided entry copy (`t1 = a0; s2 = t1`)

Proof: `work/bench/copy_probe.py`, sixteen spellings through `cpp | cc1 | maspsx` (pass oct31).
Only the 64-bit widen→narrow spelling emits the two consecutive moves, and it pays a `sra` pair, a
frame of `0x20` instead of `0x18` and an extra saved register. Applied to the real body it went from
96/119 to 119/119 at size `0x1e4`. Every source-level second-variable spelling is coalesced away.

Closed:

| body | residue that closes it | evidence |
|---|---|---|
| `func_8002E4B4` | nothing is left *of this class* — measured unchanged at 106/118 with the cast-chain copy (oct31). It remains open on the saved-register numbering `$s1..$s4` vs `$s0..$s3` | bench rows 6 and 4; body measurement 106/118 both ways |
| `func_8004ADA4` | the entry copy is the one missing word (`0x1d8` vs `0x1dc`); the two-locals spelling buys it at 106/119 | bench rows 5 and 7; body 96 → 106 → 119 |

`func_8004ADA4` is therefore closed on this class: its single-word gap *is* this class, and the class
cannot be bought.

## B. Caller-saved home (a value gcc keeps in `$a*`/`$t*` where the game keeps it in `$s*`, or the
reverse, with no copy involved)

Proof: three independent bodies reached identical size with the field in the wrong register and no
spelling moved it — `func_8001A710` (distance terms in `$a3`/`$a1` vs the game's `$a1`/`$a0`),
`func_80026478`/`func_80026870` (the twins' first sign test, fixed only by arm polarity), and the
projection body's shifted saved set. The allocator is never in question: the class is a register
*home*, and C has no spelling for "put this pseudo in a saved register".

Closed:

| body | residue | evidence |
|---|---|---|
| `func_8002050C` | `-1` limit rematerialised (`addiu $a3,$0,-1` vs `addu $a3,$v0,$0`); naming the sentinel costs 17 words | oct29 sweep, 3/25 and 4/25 |
| `func_800382C0` | `addu $v0,$v0,$a0` will not flip to `$a0,$v0`; the `0x1E000` materialisation is hoisted | oct29 sweep, 1/12 across three spellings |
| `func_8003012C` | base homed in `$v0`, index in `$v1` (the reverse of the game) | oct30, 120/124 |
| `func_8003B3CC` | base in `$v1` where the game uses `$a0`; store order | oct29, 11/19 |
| `func_8001A710` | the two distance terms home in `$a3`/`$a1` where the game uses `$a1`/`$a0`; every spelling kept the same two homes | oct29, exact size, no home moved |

`func_8002E4B4` stays open only on the saved-set numbering, not on a home; it is listed under A for
the copy measurement and must not be re-tested for the copy.

## C. Identical default blocks cross-jumped

Proof: `func_8003599C`, pass oct29e. The two dispatches' `default` arms compile to the identical five
words (`sll $v0,$a1,1; addu $v0,$v0,$a1; sll $v0,$v0,4; addu $v0,$v0,$v1; sw $zero,4($v0)`); the game
keeps two copies, gcc emitted one and branched both switches into it, and the body came out five words
short at `0x20` frame and 61/137 matching. No CFLAGS in the allowed list disables cross-jumping, so no
source shape can express the second copy.

| body | residue | evidence |
|---|---|---|
| `func_8003599C` | second dispatch's `default` block cross-jumped into the first | oct29e: frame closed 0x18 → 0x20, 2 → 61 matching, then 132/137 with the missing five words being that copy; turn-on `0x80035B90` |

## D. Prologue constant/save interleave and shared-arm fall-through

Proof: `func_80034874`, passes oct29e–oct29g. Two residues that no source shape closed, each measured:

- **prologue interleave** — the game opens `lui $a1,0xE100` / `ori`, then `addiu $a0,$sp,0x28`, then the
  `$s2`/`$s6` initials. Writing the constant before the locals seed the block moved the body 64 → 66
  matching (the only change that ever paid); the permuter then spent ~6,200 iterations on the same body
  and peaked at score **875 of 1,155**, its winning variants all permutations of exactly this region.
- **shared-arm fall-through** — the game's `.L80034A10` is `x += 8` placed *after* the body and falling
  through into `.L80034A14` (`k++`), with both skip tests branching to it. Split `||` into two `if`s:
  null at 66. If/else with the arm first: 39. Arm as the `else` (body in the `if`, arm last so it can
  only fall through into `k++`): 39 at `0x1fc` vs the game's `0x204`. gcc will not lay the arm below the
  body from any of the three orderings.

| body | residue | evidence |
|---|---|---|
| `func_80034874` | prologue constant/save interleave (`0x800348B0`) plus the shared `x += 8` arm placed after the body (`0x8003494C`, `0x80034A10`); turn-on `0x80034A10` | oct29e–oct29g: 41 → 64 → 66/129 at exact size, then 39 on the arm-as-else shape; permuter 875/1155 |

## E. Stack switch through the scratchpad (`sw $sp` / `addu $sp`)

Proof: `func_800262E8`, pass oct29i. The body writes `$sp` into the scratchpad and installs a new `$sp`
from it: `lui $v1,0x1F80` / `ori $v1,0x1F8003FC` / `addu $t0,$v1,$0` / `addiu $t0,$t0,-0x14` /
`sw $sp,0x10($t0)` / `addiu $t0,$t0,-0x4` / `addu $sp,$t0,$0`, and restores with
`addiu $sp,$sp,4` / `lw $sp,0x10($sp)`. Nine words, all of them naming `$sp` as an ordinary register.
Plain C cannot name `$sp` (the frame pointer is the compiler's), and `asm` is forbidden, so no source
shape reaches this. Measured: the whole rest of the body is already exact — with the switch omitted the
body compiles to `0x50` against the game's `0x74`, i.e. the missing 0x24 bytes *are* those nine words,
and every call, both `%gp_rel` stores and the final `func_80023BA8(0)` match.

| body | residue | evidence |
|---|---|---|
| `func_800262E8` | the nine-word scratchpad stack switch around the `func_80025B90` call | oct29i: 10/29 matching (19 words differ), size `0x50` vs `0x74`; the gap is exactly the switch |
| `func_80027538` | the same switch, same nine words, one different callee (`func_80027478`) and two different globals | oct29i: byte-for-byte the twin of `func_800262E8` outside the switch |

## F. Induction-pointer bias under a signed loop test

Proof: `func_8003B478`, passes oct29j–oct29k. The game walks two `0x70`-byte records with an
incrementing pointer and **positive** field displacements (`sh $s1,0x4($a0)`, `addiu $a0,$a0,0x70`,
`slt $v0,$a0,$t0`). Our compiler biases the induction pointer by the last field's offset (`+0x6C`), so
every store becomes a negative displacement (`sh $s1,-0x68($a0)`), and the zero-based walk is lost.
Every spelling of the walk measured, on the same draft:

| shape | result |
|---|---|
| `REC *` walk with `rec++` | **39 of 71 words match**, size `0x11c` vs `0x11c` |
| `u8 *` walk, cast per iteration, `walk += 0x70` | 39 of 71, size exact |
| `s32` address walker with explicit offsets (the signed-`slt` hypothesis) | 39 of 71, size exact |
| `first`/`start`/`end` derived from the symbol, not from the walker | 39 of 71, size exact |
| signed cast on the loop compare | 39 of 71, size exact |
| explicit `s32` index over the record array, `slti`/`1`/`0x100` invariants sourced first | **6 of 71**, size `0x110` vs `0x11c` |
| `/* cflags: -fno-strength-reduce */` | **6 of 71**, size `0x118` vs `0x11c` |

Merged evidence: 21 of 693 merged units emit a positive-displacement pointer walk with a fixed
increment — smallest `func_80016D00`, source `do { *d++ = *s++; } while (s != end);`, stream
`sw … 4(v1)`, `8(v1)`, `12(v1)` then `addiu v1,v1,16`. So the offsets are reachable; but every one of
those 21 walks tests **equality**, while this body's tail is a signed `slt`, and no merged unit pairs
positive displacements with a signed compare.

| body | residue | evidence |
|---|---|---|
| `func_8003B478` | induction pointer biased to the last field's offset (`0x8003B4D0`) and the three loop invariants sunk below the base materialisation (`0x8003B48C`); turn-on `0x8003B48C` | oct29j–k: best 39 of 71 at exact size across five pointer spellings, and 6 of 71 for both the index rebuild and `-fno-strength-reduce` |

## Retired

Twelve bodies, six classes, retired by measurement: `func_8002E4B4`, `func_8004ADA4` (A);
`func_8002050C`, `func_800382C0`, `func_8003012C`, `func_8003B3CC`, `func_8001A710` (B);
`func_8003599C` (C); `func_80034874` (D); `func_800262E8`, `func_80027538` (E); and
`func_8003B478` (F).
`lane/select.py` now classifies these as `closed` and never lists or drafts them, not even with
`--allow-attempted`; the queue census prints the count. Only rows in the two tables above are
harvested, so a body named in the proof prose is not retired by mention alone.

A body with one of these classes **plus** other differing words is still open on those other words;
add it to the table with the extra words named, and delete the row when it is drafted again.
