# pass oct31 — bench of the entry-argument copy wall

The wall, stated exactly: the game opens

    addu  $t1, $a0, $zero
    addu  $s2, $t1, $zero

Our draft's single `s2 = a0` collapses to one move (`addu $s2,$a0,$0`), so the body is one word
short and every later register assignment shifts by one.

## Bench (`work/bench/copy_probe.py`, compiled through cpp | cc1 | maspsx)

Sixteen spellings, each a complete function whose body afterwards is identical, so only the entry
sequence can differ. `n` is the whole function's word count.

| # | spelling | n | entry sequence | copy? |
|---|---|---|---|---|
| 0 | `s2 = a0` | 12 | `sw $16,16($sp)` … `addu $16,$4,$0` after the jal | no |
| 1 | typed temp `u32 t = (u32) a0` | 12 | identical to 0 | no |
| 2 | copy through a struct member | 12 | identical to 0 | no |
| 3 | read back through `&a0` | 13 | `addu $16,$4,$0`, plus `sw $4,24($sp)` | no (and one word worse) |
| 4 | `a0` live after the call | 17 | one move, `a0` spilled | no |
| **5** | **widen to `unsigned long long`, narrow back** | **21** | **`addu $18,$4,$0` / `addu $16,$18,$0`** | **yes, but costs** |
| 6 | cast chain through `char *` | 15 | one move | no |
| 7 | two locals (`t1 = a0; s2 = t1`) | 15 | one move | no |
| 8 | `a0` only in the call | 14 | one move | no |
| 9 | `a0` reused later, no call | 9 | `$4` reused directly | no |
| 10 | `a0` stored as `u32`, no call | 8 | `sw $4,8($2)` | no |
| 11 | `a0` reused, call after | 18 | one move | no |
| 12 | `a0` stored into its own struct | 5 | `$4` reused directly | no |
| 13 | `a0` reassigned later | 9 | `$4` reused directly | no |
| 14 | `a0` reassigned, `s2` used first | 9 | `$4` reused directly | no |
| 15 | two params both copied | 9 | `$4` reused directly | no |

**Only #5 emits the extra move, and it is not a copy: it is the 64→32 narrowing of a wide value, so
gcc keeps the pointer in one saved register for the wide form and materialises the narrowed one into
another.** The price is visible in the same row — frame `0x20` instead of `0x18`, an extra saved
register (`sw $17,20($sp)`), and an `sra $5,$4,31` sign-extension pair. That is why it loses on the
real body below.

Everything that would force a *source-level* second variable (7, 12, 13, 14) is coalesced away: gcc
2.8.1 will not keep two identical pointer pseudos live in this function shape. The conclusion is that
the game's `t1` is not a source temp but the parameter pseudo being split for its own reasons (the
parameter is live to a store while `$a0` is redefined at `lhu $a0,0x44($s0)`), which no spelling in
this bench reproduces at zero cost.

## Applied to the two bodies

| body | before | spelling | after | verdict |
|---|---|---|---|---|
| `func_8004ADA4` (allocator, 1 word short) | 96/119, size `0x1d8` vs `0x1dc` | #5 widen→narrow | 119/119, size `0x1e4` vs `0x1dc` | rejected: the `sra` pair and the wider frame cost more than the copy buys |
| `func_8004ADA4` | 96/119 | #7 two locals (`arg = a0`, reads through `arg`) | **106/119** | the entry copy *does* appear (`addu $t0,$a0,$0`) but a second copy appears for `a1` and the order moves; net worse |
| `func_8002E4B4` (projection) | 106/118 | #6 cast chain on the first parameter | 106/118 | unchanged — its residue is the saved-register numbering (`$s1..$s4` where the game uses `$s0..$s3`), not the entry copy |

## State

**Conversions 0, bodies attempted 2** (`func_8004ADA4`, `func_8002E4B4`); two shapes on the first.
The wall is now **measured, not assumed**: no spelling produces the game's copy at zero cost, and the
one that produces it is a 64-bit artifact that widens the frame.
