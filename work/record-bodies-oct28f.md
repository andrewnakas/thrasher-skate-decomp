# Bodies-only pass, 2026-10-28 (vi)

No new tooling. One conversion, four attempts, five bodies touched, sorted ascending by residue.

## Conversion

| function | words | how it closed | PR |
|---|---|---|---|
| func_80047B28 | 91 | store the allocator result into the record **before** the null test | [#202](https://github.com/andrewnakas/thrasher-skate-decomp/pull/202) — MERGED |

The block copy was never the problem. The residue was carried over as "the 0x80-byte copy
expands to lwl/lwr+swl/swr pairs" from an earlier pass; in fact `memcpy` reproduces it, and the
19 lost words lived in the *order* of two statements:

```c
    p = (u8 *) func_80034C20(*(s32 *) (a1 + 8) * *(s32 *) (a1 + 0xC));
    *(u8 **) (a1 + 0x14) = p;      /* <- the store is before the test, not after */
    if (p == 0) {
        return 0;
    }
```

Written as the natural `p = ...; if (p == 0) return 0; *(u8 **)(a1 + 0x14) = p;` the compiler
keeps the pointer live across the branch and loses the delay slot plus the copy shape. Storing
the result into the record first, then testing the register, is the game's order and matches
exactly. **Banked: when a call's result is both tested and stored, store it first if the listing
stores before it branches.**

## Attempts (all parked, class named)

| function | words | best | residue | turn-on instruction |
|---|---|---|---|---|
| func_80017740 | 95 | 9/95 (size exact) | two parameter homes swapped | `addu $s4, $a1` / `addu $s5, $a0` at 0x80017748/0x80017750 — the game gives the *second* parameter s4 and the first s5; gcc 2.8.1 hands them out in parameter order |
| func_80018118 | 96 | 9/96 (size exact) | same swap, same body | 0x80018120/0x80018128 |
| func_80023D2C | 102 | 66/102 (0x180, want 0x198) | six load-delay `nop`s absent from the stack-vector builds | `lw $v0,0x44($s5); lw $v1,0x44($s0); nop; subu` at 0x80023D98 — the object pointer and its derived V3 pointer must both stay live; the inline form loses the frame (0x40) and the named form loses the nops |
| func_800504D4 | 100 | 42/100 (size exact) | callee-saved naming cascade | `addiu $s5, $zero, -0x1` at 0x80050590 — the −1 sentinel is materialised before the base address, and the countdown/comparison pair holds s1/s0 where ours holds s0/s1 |

### What the two twins proved

They are the same function modulo the entry tag (`!= 0` vs `!= 0x8000`), the base offset
(0x0C vs 0x10) and the final call. Both closed to an exact size on the same three levers —
store-then-test for the flag word, separate variables for the two lookups, and the default-store
before the guard — and both stopped at exactly one residual: **which of s4/s5 holds each
parameter**. Two independent bodies at the same one-class residue is the cleanest statement yet
of the allocation wall, and the turn-on instruction is named above so it can be checked.

The other two residues confirm the same pattern from the opposite direction: `func_800504D4`
reaches an exact size and then differs only in which callee-saved register holds the sentinel,
and `func_80023D2C` differs by exactly the six load-delay `nop`s that gcc's scheduler inserts
when it cannot fill a slot — not by any source-expressible feature.

## Volume accounting

- attempted: 5 bodies (80047B28, 80017740, 80018118, 80023D2C, 800504D4)
- converted: 1 (80047B28, merged)
- parks: 4, all in the allocation/scheduler classes, each with the turn-on instruction named
- pipeline: `scan` 680 files 0 problems, `gate` 680/680, `build` `SLUS_009.35: OK
  (16829afba66533e2645bf87af2774671b06ff36b)`
- two earlier PRs still open: [#199](https://github.com/andrewnakas/thrasher-skate-decomp/pull/199) (func_8004B088),
  [#200](https://github.com/andrewnakas/thrasher-skate-decomp/pull/200) (func_8001E3A0)

## Queue

`select.py list --fresh` at this tree: **41 open in the 95-140 word band**, 216 bodies with a
recorded attempt, 680 merged. The small bands are exhausted; everything left is ≥95 words and
call-bearing.

## Read for the next pass

The store-then-test lever is new and free — it should be applied to every park whose listing
writes a value before branching on it. The four parks above are all one class and should not be
re-opened without a tool that can name a register home; a C pass will not move them.
