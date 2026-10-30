# Pass oct29i — six bodies, one at 25 of 31, and the base-CSE class named

Tree `7605c52` = `origin/main`; no branch switched, no unit file left behind (693 before and after).
Gate **693/693 PASS**, build **PASS** sha1 `16829afba66533e2645bf87af2774671b06ff36b`.

All residues below are **matching/total** (the lane convention); `match.py` prints the converse.

## The bodies

| body | first | best | size | residue |
|---|---|---|---|---|
| **`func_8003BDB8`** | 6/31 | **25/31** | exact | the `0xFFFF0000` constant's live range: the game emits `lui $v1,0x1` **and** `lui $v0,0xFFFF` before the four stores; we rematerialise it after them. Turn-on `0x8003BDBC` |
| `func_80029488` | 11/29 | 14/29 | `0x20` vs `0x28` | frame 8 bytes short (locals the listing never references) plus the `$s0`/`$s1` role swap for `p`/`n` |
| `func_800494A4` | 0/32 | 8/32 | `0x84` vs `0x80` | index global's split address CSE'd into `$s1` across the loop call |
| `func_800387C8` | 5/37 | 5/37 | `0x90` vs `0x94` | same class: `lui` base of the index global hoisted into `$s0` across `func_80059FFC` |
| `func_800262E8` | 10/29 | — | `0x50` vs `0x74` | the nine-word scratchpad stack switch — **closed by evidence** (section E) |
| `func_80027538` | — | — | — | twin of the above — **closed by evidence** (section E) |

## What moved

`func_8003BDB8` went 6 → 25 of 31 with two mechanically-decidable fixes, both banked rules applied
properly for once:

1. **`u8 D_8008234C[]` folded `+0x128` into the symbol** (`0x80082474` in the diff) and dropped the three
   `0x1000` stores into the `jal`'s shadow. Declaring the base `u32` and indexing `D_8008234C[0x4A]`
   scales the constant index into a displacement, so the base stays the accumulator and the offset stays
   `0x128/0x12C/0x130` — that one change is most of the 19 words.
2. Naming the two constants as locals (`one`, `hi`) instead of writing literals at each store stopped
   `lui $v0,0x1` from being re-materialised per store.

The remaining six words are one decision: gcc sinks `lui $v0,0xFFFF` below the four `0x10000` stores
because the constant is cheap and `$v0` is free; the game keeps it live across them. Measured and
rejected: declaring `hi` before `one` (no change, 6 differing words), and storing `D_8008B260` first in
source (**worse**, 9 differing — the scheduler then sinks the base materialisation instead). This is the
constant-hoist class, not a source shape, so the body is parked rather than hunted.

`func_80029488` gained the missing entry parameter: the game passes the magic tag in `$a1` and `1` in
`$a2`, so `$a0` is forwarded as the call's first argument. Writing `func_8001D5B0(a0, 0x4954414D, 1)`
fixed the delay slot and the tag's register (11 → 14 of 29). Its frame is still 8 bytes short with
nothing in the listing writing there, and swapping the two locals' declaration order did **not** move the
`$s0`/`$s1` roles (measured), so both residues stand.

## The class that now blocks three bodies: split-address base CSE

`func_800387C8`, `func_800494A4` and (partly) `func_80029488` fail the same way: an extern symbol
appears twice around a call, and gcc 2.8.1 CSEs the `lui`/`%lo` pair into a **callee-saved** register,
which then costs a save and a restore; the game re-materialises the address at each use instead. In
`func_800494A4` the hoist is what grows the frame from `0x18` to `0x20` and puts the size one word over.

The widened-extern rule did work there first: `extern s32 D_8008A800;` compiled gp-relative where the
game uses `lui`/`lw`, and widening it to `s32 D_8008A800[4]` took the body 0 → 8 of 32 and made the
`blez` and the `$s0 = 0` seed match. What remains is only the base's register.

Measured lever: `/* cflags: -O1 */` on `func_800494A4` — **worse**, 36 of 32 differing (more words than
the function has) at size `0x90`, against 24 of 32 at `0x84` under `-O2`. It still hoists the base, just
into `$s0` instead of `$s1`, and loses the delay-slot fills. The allowed-flag list offers nothing here
and the source cannot name a `lui`, so this joins A and B in the "the allocator decides, C cannot say
it" family. Not retired — three bodies is not the proof A–E carry — but no future pass should spend
`-O1` on it again.

## Bookkeeping note

The selector already carried all four of these bodies as attempted (from earlier census rows), so the
census barely moves: 262E8 and 27538 left `attempted` for `closed`. Its printed "best" is the *lowest*
matching count rather than the highest, so it read `func_8003BDB8` as `6/31` — this pass's 25/31 is not
visible to it. That inversion is only cosmetic today (it never gates selection), but the row format is
ambiguous between `matching/total` and `size/matching`, so it is not fixable by flipping the comparison
without first disambiguating the rows.

## Count

Conversions **0**, bodies measured **6**, new closures **2**. No PR.
Queue at `7605c52b`: **71 open in range**, 237 attempted, 693 merged, 11 closed-by-evidence.
