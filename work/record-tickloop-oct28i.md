# Tick loop closed, sweep narrowed, 2026-10-28 (ix)

Conversion 1 (func_8004AC1C, PR #204, merged by Steward), parks 2, and the sweep narrowed from
51/17 to 15/5 with the two wrongly-offered bodies proved rejected.

## Conversion

**func_8004AC1C** — 98 words, matched after three shapes:

1. the slot index must be masked before scaling (`D_800AEA24 + (i & 0xFF) * 4`), which keeps the
   address built per iteration instead of walked: 86 → 22 words;
2. the unsigned comparisons (`u32` slot, budget and counters) give `sltu`/`sltiu`: 22 → 5;
3. **the budget decrement is written twice, once in each arm of the size test**, so gcc keeps a
   single store and computes `capacity - used` in the branch's delay slot: 5 → MATCH.

`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`, unit sha1
`a38500265432f295fbe51e743b7e79718d65d3e5`. **Banked:** when a listing computes a difference in
the delay slot of the branch that skips the slow path, the source writes the assignment in *both*
arms and gcc merges the store.

## Parks

| function | words | was | now | residue | turn-on |
|---|---|---|---|---|---|
| func_800380BC | 129 | 123/129 | 91/129 (0x1f8, want 0x204) | three words short; ten live callee-saved values needed | the destination copy `addu $s0,$a1` at 0x800380C8 — the parameter is copied to *two* variables (0x800380C8 and the `s6 = s0` at 0x8003821C), and no single-name draft keeps both |
| func_80047C94 | 151 | — | 146/151 (0x284, want 0x25c) | ten words over; the row loops | `addiu $a0,$sp,0x10` at 0x80047CB0 — the name block sits below the header block, so the name array is declared first, and the two row loops each need their own index pair |

`func_80047C94` is the store-first body the narrowed sweep selected: `jal func_80034C20` with
`sw $v0, 0x14($s5)` in the `bnez` delay slot, i.e. the allocation is stored into the record before
it is tested. That half of the draft is right; the row loops are what is over.

## The narrowed filter

`work/scan_storefirst.py` now requires the call's result to be **stored into a record** (base not
`$sp`/`$gp`) *and then* branched on, which is what the lever actually needs:

- loose signature (branch on a result): **51 listings, 17 open**
- narrowed signature (store into a record, then branch): **15 listings, 5 open**

Open under the narrowed signature, ascending: `func_80047C94` (151), `func_80015A94` (169),
`func_80052874` (231), `func_80050A3C` (408), `func_80028498` (535).

Proof on the two it wrongly offered last pass: `func_800380BC` is **rejected** (it branches on
`MemCardReadData` without storing it). `func_8004AC1C` still matches, because it does contain a
store-then-branch site — the one at `sw $s0, 0x38($s1)` — so its presence was not an error, only
irrelevant to the body it was offered for. The filter is a listing-level test, not a
body-level one; the body still has to be read.

## State

- attempted 3, converted 1, parks 2
- pipeline: `scan` 683 files 0 problems, `gate` 683/683, `build` OK
- worktree check: 683 local = 683 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 683 merged before this pass's merge; +1 unit merged
