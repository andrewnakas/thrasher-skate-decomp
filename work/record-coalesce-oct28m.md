# Free-list coalesce fixed; mode-machine decode corrected, 2026-10-28 (xiii)

Conversions 0, bodies attempted 2 (`func_80015A94` twice over, `func_80052874` decode
corrected), parks 3.

## func_80015A94 — the named mis-decode, fixed, and what it bought

The coalesce path was wrong in exactly the way recorded: I had written a content check where the
listing does pointer arithmetic. Rewritten as pointer-sum equality with summed sizes —

```c
    if (prev != 0 && (u8 *) blk + *(u32 *) (blk + 8) == prev) {
        *(u32 *) (blk + 8) += *(u32 *) (prev + 8);
        ...
    }
    if (next != 0 && (u8 *) next + *(u32 *) (next + 8) == (u8 *) blk) {
        *(u32 *) (blk + 8) += *(u32 *) (next + 8);   /* sum, not either alone */
```

| form | result |
|---|---|
| draft with content check | 158/169, size 0x1b8 (59 words short) |
| pointer-sum equality + summed sizes | 165/169, size 0x274 (12 words short) |
| + `p` computed before the null test (so it lands in `beqz`'s delay slot) | **116/169, size 0x278 (10 words short)** |

**The single correction moved the body 47 words** — far more than any spelling this lane has tried
on it. The second change (compute before the test) is the store-then-test family again and bought
two more words plus 49 of alignment.

**Next named residue:** the insert's block pointer is homed one register high — the listing's
`sw $zero, 0x4($s0)` at 0x80015B54 is our `sw $zero, 0x4($s1)` — the same argument-register
binding class as the twins and the image body, now confirmed a third time. The structure is right;
only the homes disagree.

## func_80052874 — the decode was wrong: it is not a switch

Checked before drafting, as instructed. There is **no jump table** for this function: the only
`jr` in the whole listing is the `jr $ra` at 0x80052C08. The dispatch is an if-chain on
`D_8008A9FC` (`beqz` at 0x800528A4, `bne 1` at 0x800528B0, `bgtz` on `D_8008A9F0` at 0x800528C0),
so the previous record's "write it as a `switch` with the table's case order" was a wrong
prescription and is corrected here. Turn-on instruction: `beqz $v1, .L80052934` at 0x800528A4 —
an `if/else if` chain in the listing's arm order, which for a chain is the code order.

Not drafted this pass; the body is 231 words and the correction is what the check was for.

## Strength-reduce flag, measured effect (carried forward)

On `func_80047C94`: baseline 147/151 @0x27c → flag on **125/151 @0x26c**. It restores positive
displacements off a walking pointer and does nothing for ordering. That is the whole of its
effect on this lane so far.

## State

- attempted 2, converted 0, parks 3
- pipeline: `scan` 684 files 0 problems, `gate` 684/684, `build` OK
- worktree check: 684 local = 684 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 684 merged; narrowed sweep open set 5,
  `func_80015A94` now at 116/169 with one named residue
