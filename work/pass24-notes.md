# Pass 24 — transcription, no new tooling

Branch base: `freebuff/records-oct26` for records; units cut from fresh `origin/main` (6eaff67, 648 units).

## Conversions

| body | words | verdict |
|---|---|---|
| func_80020C34 | 80 | **MATCH** (2 shapes). Nested type/sub dispatch onto four record tables; strides 1440/4800/1920/10800 read off the emitted shift chain. The `return 0` inside every case blocked gcc's cross-jump; a single trailing `return 0;` with `break;` per case reproduced the shared tail in one step. PR #162. |
| func_80021894 | 85 | **MATCH** (2 shapes + 3 corrections). Free-record thread: `(id & 0xFF00) >> 8` (mask then shift, not shift then mask), `D_8009C6D4[D_8008A2A8++]` (one counter read), the `+3` store rebuilt as `*((u8 *) tab + 0x30 * low + 3)` so the address-taken `tab` is reloaded, and `(u32) offset + (u32) tab` for the `addu` operand order. PR #163. |

## Parks

**func_80049530** (79 w) — 4 shapes, best 66/79, `0x140` vs `0x13c`. Residue: the game folds the
record base into a register (`addiu $s0, $v0, 6` after `%lo(D_800828B4)`) and our build folds the `+6`
into the `%lo` (`0x800828BA`); the first loop's bound is cached in `$a2` while ours reloads the global;
one extra saved register because `q` survives the inner countdown. `-mno-split-addresses` makes it
worse (82/79, `0x14c`).

**func_800219E8** (99 w) — 3 shapes, 54/99, `0x190` vs `0x18c` (one word long). Structure already
matches (guard, `sh` of `rec[1] + extra` into `+0xE`, push onto `D_8009C0A4`, compaction of the free
stack, chain walk). Residue: the game caches the table pointer in `$t2` across the loop and re-derives
the node from it, while this build reloads the stack slot per iteration and needs one extra word;
parameter copies are saved `$s1` before `$s0` in the game, `$s0` first here; the two counter loads are
scheduled before the `u16` add in the game. Class: live-range order across the loop, not source shape.

Queue after this pass: 648 units on `origin/main` + 2 open unit PRs (#162, #163).

**func_8001A710** (73 w) — 2 shapes, 55/73, `0x134` vs `0x124`. Structure decoded and present: the
list comes from `func_8001A6F8(&n)` with `n` address-taken (hence the store/reload of the count each
iteration), the loop is `n = n - 1; n != -1; n--` walking a 0x18-stride slot array, flags test at +4,
deltas at +0xC/+0x14/+0x10 shifted `sra 16` and negated. Residue: the game keeps three dead stores at
`sp+0x10/0x14/0x18` while its multiplies still read the registers; writing the three as an `s32 d[3]`
reproduces the stores but forces a reload before every `mult` (four extra words), and writing them as
plain locals drops the stores. Class: gcc's store/load forwarding on a local aggregate, not a source
shape this compiler can be steered into by index order.

**func_8003A1B8** (71 w) — 2 shapes, 62/71, `0x124` vs `0x11c` (two words long). Decoded and present:
`kind != 2` early return, the 8-byte descriptor at `D_800A8404 + 8 * (h[0] >> 8)`, the 12-byte stack
header `{f0, f2, f4, f6, f8, fA}` handed to `SetDrawLoad`, the two packed words
`((a >> 6) & 3) | (((a >> 14) & 3) << 5) | (((a >> 22) & 3) << 10)` (which combine folds into the
game's `srl 9/andi 0x60` and `srl 12/andi 0xC00` — a `u16` bitfield struct was measured first and is
worse, `0x144`, because the field writes become read-modify-write of the stack slot), and the
`0xFF000000`/`0xFFFFFF` link fixups. Residue: store schedule inside the header (`f4` first here, `f0`
first in the game) and two words of register pressure around the descriptor reads.

## Pass 24b — family round two: no conversions, one lever banked

Base `origin/main` 44b57be (650 units). All candidates checked against freshly fetched main before
drafting; `func_80057E9C` and `func_80021894` confirmed merged (#161, #163).

**func_800219E8 (99 w) — 55 → 38/99, size exact, then parked.** The lever asked for works: copying
the address-taken table local into a plain local before the loop (`base = tab;`) stopped the per-
iteration `lw 0x18($sp)` and put the pointer in `$t2` like the game, taking the body from 55 to 38
words with the size going exact (`0x18c`). It did **not** move the prologue: the game saves `$s1`
(`extra`) before `$s0` (`id`), this build the other way round, and the loop's compaction
index/count homes (`$a3`/`$t0` vs `$a1`/`$a0`) stay swapped. Also measured, no movement:
explicit entry copies in both orders (38), `key = id` moved after the guard (78, size short),
`-fno-schedule-insns2` (99/99), `-O3` (38). Class: saved-register pairing + loop live ranges,
already recorded as compiler-bound.

**func_80020D74 (39 w) — rechecked, 4/39, unchanged.** The single relocated instruction is the
`or` that builds `r`: the game emits it before the guard's `lw`, this build lets `reorg` sink it
into the `beqz` delay slot, which shifts the rest by one word. Delay-slot filling, issue #17. No
shape changed it; it stays closed.

**func_8002AC14 (86 w) — 76/86, 0x150 vs 0x158, parked.** Whole body decoded and present (outer
count at `+5`, per-sector vertex count at `+1`, vertex record 8 bytes, 0x1C-stride tab through
`D_800A4F00[1] + 156*i`, `dst = mat + 12*idx`, three `clamp(base + ((light-128) * (w<<9) >> 16))`
stores). Residue: gcc hoists the three `-0x80` biases to function entry where the game
re-materialises them inside the loop, and the `D_800A4F00 + 4` base folds into `%lo`. Both are
LICM/address-fold classes.

**func_80055FC4 (80 w) — 73/80, best `0xb4` and `0x16c` vs `0x140`, parked.** Jump-table body;
a table *is* emitted (`jr $v0`, `sltiu 0xC`), so the dispatch itself is reachable. Residue: the game
re-derives the whole `D_800B2428 + 112 * D_8008B4DC` address inside every arm (7 instructions each),
and gcc cross-jumps the case bodies into one shared block when the record pointer is indexed afresh
(`0x16c`) and drops the recomputation entirely when it is cached (`0xb4`); no spelling produced both
the duplication and the table at the game's size.

Queue after this pass: 650 units on main, 378 bodies unmatched. No unit PR from 24b.

**func_8001D1E8 (71 w) — 3 shapes, best 69/71 at `0x114` vs `0x11c`, parked.** Decoded: three-way
dispatch on the second parameter, each arm calling `func_8001D304(table + 4*idx, &slot)` then
returning `func_8001D340(a, b, arg & 0xFFFF, &slot) ? &slot : 0`, with slots `D_8008AE20/28/30`
(8 bytes each, address-taken → `addiu $x,$gp`), case 0's callee arguments read from the 8-byte
`D_8006F254[idx]`, cases 1 and 2 passing the constants `D_8006EF88`/`0xC` and `D_8006EE94`/`0x30`.
Residue: this build puts `idx` in `$s1` and `arg` in `$s2` (three saved registers, the game has
`$s0`/`$s1`), and the dispatch comes out as a `slti` range test where the game has the compare chain
`1, 0, 2`; spelling it as an if-chain in that order (0xfc) and as a ternary return (0x134) both move
away. Class: saved-register pairing plus gcc's case ordering, both recorded as compiler-bound.
