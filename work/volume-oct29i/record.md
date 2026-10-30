# Pass oct29i — six bodies, one at 6 of 31, and the base-CSE class named

Tree `7605c52` = `origin/main`; no branch switched, no unit file left behind (693 before and after).
Gate **693/693 PASS**, build **PASS** sha1 `16829afba66533e2645bf87af2774671b06ff36b`.

## The bodies

| body | first | best | size | residue |
|---|---|---|---|---|
| **`func_8003BDB8`** | 25/31 | **6/31** | exact | the `0xFFFF0000` constant's live range: game emits `lui $v1,0x1` **and** `lui $v0,0xFFFF` before the four stores; we rematerialise it after them. Turn-on `0x8003BDBC` |
| `func_80029488` | 18/29 | 15/29 | `0x20` vs `0x28` | frame 8 bytes short (locals the listing never references) plus the `$s0`/`$s1` role swap for `p`/`n` |
| `func_800494A4` | 32/32 | 24/32 | `0x84` vs `0x80` | index global's split address CSE'd into `$s1` across the loop call |
| `func_800387C8` | 32/37 | 32/37 | `0x90` vs `0x94` | same class: `lui` base of the index global hoisted into `$s0` across `func_80059FFC` |
| `func_800262E8` | 19/29 | — | `0x50` vs `0x74` | the nine-word scratchpad stack switch — **closed by evidence** (section E) |
| `func_80027538` | — | — | — | twin of the above — **closed by evidence** (section E) |

## What moved

`func_8003BDB8` went 25 → 6 by two mechanically-decidable fixes, both of them banked rules applied
properly for once:

1. **`u8 D_8008234C[]` folded `+0x128` into the symbol** (`0x80082474` in the diff) and put the three
   `0x1000` stores *after* the `jal`. Declaring the base `u32` and indexing `D_8008234C[0x4A]` keeps the
   base as the accumulator and the offset as a displacement, which is what the game does — that single
   change took it from 25 differing words to 6.
2. Naming the two constants as locals (`one`, `hi`) instead of writing literals at each store kept
   `lui $v0,0x1` from being re-materialised per store.

The remaining six words are one decision: gcc sinks `lui $v0,0xFFFF` below the four `0x10000` stores
because it is a cheap constant and `$v0` is free; the game keeps it live across them. Tried and measured:
declaring `hi` before `one` (no change, 6), and storing `D_8008B260` first in source (9, worse — the
scheduler then sinks the base materialisation instead). This is the constant-hoist class, not a source
shape.

`func_80029488` gained the missing entry parameter: the game passes the magic tag in `$a1` and `1` in
`$a2`, so `$a0` is forwarded as the call's first argument. Writing `func_8001D5B0(a0, 0x4954414D, 1)`
took it 18 → 15 and fixed the delay slot. Its remaining frame is 8 bytes short with nothing in the
listing writing there, and swapping the two locals' declaration order did **not** move the `$s0`/`$s1`
roles (measured), so both residues stand.

## The class that now blocks three bodies: split-address base CSE

`func_800387C8`, `func_800494A4` and (partly) `func_80029488` fail the same way: an extern symbol
appears twice around a call, and gcc 2.8.1 CSEs the `lui`/`%lo` pair into a **callee-saved** register,
which then costs a save and a restore; the game re-materialises the address at each use instead. In
`func_800494A4` the hoist is what grows the frame from `0x18` to `0x20` and puts the size one word over.

Measured lever: `/* cflags: -O1 */` on `func_800494A4` — **worse**, 36/32 differing at size `0x90`
(vs 24/32 at `0x84` under `-O2`). It still hoists the base, just into `$s0` instead of `$s1`, and loses
the delay-slot fills. So the allowed-flag list offers nothing here, and the source cannot name a `lui`:
this joins A and B in the "allocator decides, C cannot say it" family. Not yet retired — three bodies is
not the kind of proof A–E carry — but no future pass should spend `-O1` on it again.

## Count

Conversions **0**, bodies measured **6**, new closures **2**. No PR.
Queue at `7605c52b`: **65 open in range**, 245 attempted, 693 merged, 11 closed-by-evidence.
