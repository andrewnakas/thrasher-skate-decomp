# Image body, three measured fixes; two decode parks, 2026-10-28 (xi)

Conversions 0, bodies attempted 1, parks 3 (one worked, two decoded).

## func_80047C94 — three fixes, measured one at a time

| # | fix | result | verdict |
|---|---|---|---|
| 1 | entry guard written once: `if (a2 != 0) { for (i = 0; i < n; i++) ... }` instead of `if (a2 != 0 && n > 0)` | 146/151 @0x284 → **147/151 @0x27c** | **paid** — two of the ten words were the folded guard |
| 2 | declaration order of locals (`s32 i;` declared first) | 147/151 @0x27c → 147/151 @0x27c | **null** — the homes did not move |
| 3 | pointer advance in the delay slot | not applied | the residue is not a spelling |

Fix 2 is a second independent confirmation of the twins' finding: **declaration order and
read-order do not move callee-saved homes.** The game holds a0/s2, a1/s5, a2/s1; the draft holds
a0/s0, a1/s4, a2/s1. Two bodies, two different attempts at the same lever, no movement. That
narrows the filed allocation issue: the class is not "declare it differently", it is the
argument-register binding, which C cannot express.

Fix 3 was diagnosed but not applied, because it is not a spelling: gcc strength-reduces
`dst[0..3]` with `dst += 4` into a base at the largest displacement with negative offsets —

```
game:  addu  $v1, $s2, $zero     lbu $v0, 0x0($v1) ... lbu $v0, 0x3($v1)
ours:  addiu $a0, $s2, 0x3       lbu $v0, -0x2($a0) ... lbu $v0, -0x1($v1)
```

— which is exactly the strength-reduce shape, in the opposite direction from the banked lever
(that one wanted the flag *on*). Emitting the game's form needs `-fno-strength-reduce` on the
file, which is a compiler-flag question, not a body question. Parked at 147/151 @0x27c.

## Decode parks for the two larger members

**func_80015A94** (169) — decoded to 0x80015B20. Entry guard on a block count: `p = D_8008AD38 -
(a0 << 4)`, rejected when `p < D_8008AD3C` (unsigned) or `*p == 0`; then three calls around a
`memset(block, 0xFF, size)` and the accounting decrements `D_80089F70 -= 1`,
`D_80089F6C -= size`. The remainder is a **three-way sorted insert into a free list** keyed by
address with `D_8008AD4C` as head and `-1` as the sentinel: the `sltu` at 0x80015B34 chooses
"prepend" versus "walk", the walk at 0x80015B68 advances while `node < new` and `node->next`
exists, and the three store sites at 0x80015B48/0x80015B80/0x80015BB8 are the three cases.
Turn-on instruction: `sltu $v0, $s0, $v1` at 0x80015B34 — the comparison must be unsigned, and
the three insert cases each write **two** links in a fixed order (`prev->next`, then `new->prev`,
then `new->next`).

**func_80052874** (231) — opened for the first time, decoded to the dispatch. It is a mode
machine on `D_8008A9FC`: `beqz` → init, `bne 1` → other modes, and the init arm clears
`D_800B13DC` for 0x90 bytes, stores a zero byte into `D_800B134E`, clears `D_8008A9F4` and
`D_8008B454`, and calls `func_8005CBD8(0)` then `func_8005CBEC(7, 0, 0)`. Turn-on instruction:
`beqz $v1, .L80052934` at 0x800528A4 — the switch arms must be written as a `switch` on
`D_8008A9FC` with the real case order read from the jump table, not as an if-chain.

## State

- attempted 1 (three measured shapes), converted 0, parks 3
- pipeline: `scan` 684 files 0 problems, `gate` 684/684, `build` OK
- worktree check: 684 local = 684 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 684 merged; narrowed sweep open set 5
