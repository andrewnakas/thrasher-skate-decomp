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
