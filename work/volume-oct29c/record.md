# Pass oct29c — the walker's records, and the next park

Tree `7605c52b` = `origin/main` throughout; no branch switched.

## `func_80034874` — records named, frame closed

The first draft declared one flat `u8 buf[0x30]` and got a 0x70 frame. Declaring the three records the
listing indexes, in listing order, closed the frame to the game's **0xC0** and every local to its exact
offset:

| symbol | offset | how it is declared |
|---|---|---|
| primitive | `0x10` | `REC1` (0x18 bytes, fields at 3/4/5/6/7/8/0xA/0xC/0xD/0xE/0x10/0x12) |
| header | `0x28` | `REC2` (8 bytes, `f3` at 3, `f4` at 4) |
| work record | `0x30` | `REC3` (0x60 bytes, `s16` at 4 and 6) |
| limit | `0x90` | plain `s32` after `REC3` |

Saves then start at 0x98, so 0xC0 is exactly the frame the game builds. Result: **127/129 words**, and
the diff is now only homes and order — `addiu $s6,$v1,-0x8` where the game has `$s7`, `$v0` vs `$v1`
for the limit, and `lhu 0x2($gp)` where the game materialises `$s5` and uses `0x2($s5)`.
The 2 missing words are the inner loop's bound: the game re-materialises `D_800A5C80` inside the loop
(`lui $a2` in the back-edge delay slot, `addiu $a2` at the head) where ours hoists it once into `$fp`.
Turn-on: `0x80034930`.

## `func_8003599C` — second zero register recovered

Adding the separate zero term the listing keeps in `$t1` (`v0 = a0 + t1`, then the ×12 scale) took the
first fill loop from 129 to **134/137**. Still 3 short: the two dispatch blocks' call setup.
Turn-on: `0x80035A48`.

## The strength-reduce rule, positively stated

`-fno-strength-reduce` converts only where the induction variable is a **single scalar pointer** — that
is the case it closed on `func_8003031C` (81 → 87, displacements restored). It is measured **null** on
both remaining fold parks: `func_80020608` is 0x1dc with and without it, and `func_8002ECB8` is
byte-identical. Those two loops carry a base *and* an offset in two registers, and the flag collapses
that pair instead of preserving it. **Do not spend it again on either body.**

## Count

conversions **0**, bodies measured **2** this pass (`func_80034874` 127/129, `func_8003599C` 134/137).
No PR. Queue at `7605c52b`: 74 open (fresh), 238 attempted, 693 merged units.
