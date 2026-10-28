# gp-address population, next band (>50 words), 28 Oct 2026

Method unchanged: prologue-first, the split spelling, then the two levers banked last pass (indexes declared
before the first store; gp-relative index inlined, not cached). Permuter reserved for 1-2 word bodies.

## Conversions: 0 of 2 attempts

| body | words | best measurement | residue / class |
|---|---|---|---|
| func_8002DFF8 | 55 | 35/55 differing, 1 word short (0xd8 vs 0xdc) | block layout: after restructuring the outer test to `if (node[0] == 0x70) { ... return; }` the whole 0x70 block landed in the game's order and the 0x6C tail moved to the shared epilogue (43 -> 35 words). What remains is the abs-compare form: the game materialises `D_8008B064` **before** the `bgez`/`negu` and compares `abs < lim`, we load it after and invert the `slt`. Class: scheduling + compare form. |
| func_80030518 | 55 | 21/55 differing, 1 word short (0xd8 vs 0xdc) | the symbolic store: game emits `lui $at,%hi(S); sw $v0,%lo(S)($at)` where we emit `lui $v1` + `sw ... %lo($v1)`. `/* cflags: -mno-split-addresses */` **does** produce the `$at` form (and makes the size exact, 0xdc) but then moves the `lui $s0,%hi(D_8008A3B0)` that belongs in the `jal func_8004AB44` delay slot to after the call, costing more words than it saves (30 vs 21). Class: address materialisation vs call-slot placement — the two cannot be satisfied together in this file. |

## What this band taught (measured, not asserted)

1. **Outer-test polarity sets the whole block layout.** func_8002DFF8's `if (kind != 0x70) {...; return;}` form
   cost 43 differing words; writing `if (kind == 0x70) { ... return; }` and letting the 0x6C case fall through
   took it to 35 with no other change. Same family as the inverted-callee-test lever from the record family.
2. **`-mno-split-addresses` is not free.** It fixes a direct symbolic store to the `lui $at` form the game
   uses, but it also suppresses the split-address hoist that puts a `lui` into a neighbouring `jal` delay slot.
   On func_80030518 the two wants conflict inside one function; the flag is only a win when the body has no
   call whose delay slot the game fills with a `lui`.

## Queue

Fresh `origin/main`: 662 merged units, clean enumerator **355** unmatched bodies, 185 never drafted. Both
bodies worked here remain open; best drafts are `work/best/func_8002DFF8.c` and
`work/best/func_80030518.c`.
