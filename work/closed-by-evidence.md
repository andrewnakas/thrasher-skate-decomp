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

## Retired

Eight bodies, three classes, retired by measurement: `func_8002E4B4`, `func_8004ADA4` (A);
`func_8002050C`, `func_800382C0`, `func_8003012C`, `func_8003B3CC`, `func_8001A710` (B); and
`func_8003599C` (C).
`lane/select.py` now classifies these as `closed` and never lists or drafts them, not even with
`--allow-attempted`; the queue census prints the count. Only rows in the two tables above are
harvested, so a body named in the proof prose is not retired by mention alone.

A body with one of these classes **plus** other differing words is still open on those other words;
add it to the table with the extra words named, and delete the row when it is drafted again.
