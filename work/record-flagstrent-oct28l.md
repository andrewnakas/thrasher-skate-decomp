# Strength-reduce flag, free-list insert, 2026-10-28 (xii)

Conversions 0, bodies attempted 2, parks 3 (one worked, one drafted, one decoded).

## The flag experiment: it moves and it does not close

`/* cflags: -fno-strength-reduce */` on `func_80047C94`:

| form | result |
|---|---|
| baseline (no flag) | 147/151, size 0x27c |
| **flag on** | **125/151, size 0x26c** |
| flag on + separate source walker (`p = src`) | 125/151, size 0x26c |

**What the flag fixed:** the negative-displacement base. The draft's
`addiu $a0, $s2, 0x3` / `lbu $v0, -0x2($a0)` became the game's
`addu $v1, $s2, $zero` / `lbu $v0, 0x0($v1)` — the walking pointer with positive offsets is
back, and four words of the ten are gone.

**What it did not fix:** the remaining four words are an *ordering* difference, not a
displacement one. The game emits `s0 = 0` inside `blez $a0`'s delay slot and `a2 = $s1` after the
count test; the draft emits `dst = a2` before `blez`. No spelling tried (initialising `dst` and
`p` in the `for` init, reordering the assignments, moving the guard) moved it. The body sits at
125/151 @0x26c with the flag on; that is the better form and it is what is parked.
**Banked:** the strength-reduce flag is the lever for a displaced-base residue, and only for that.

## func_80015A94 — free-list insert, drafted, 158/169 @0x1b8 want 0x2a4

Written whole from the decode: block-count guard, the three calls around `memset(blk, 0xFF,
size)`, the two accounting decrements, and the three-way insert. **59 words short** — the second
half is wrong, not merely unpolished. The coalesce path at 0x80015BD0 tests
`blk->prev + blk->size == blk->next` with `addu $a0, $s0, $a1` and merges by adding the sizes
(`addu $v0, $a1, $v0` then a store), and the mirror case at 0x80015C4C does the same against
`blk->next`. My draft wrote a content check where the listing has pointer arithmetic.

Turn-on instruction: `addu $a0, $s0, $a1` at 0x80015BE8 — the merge test is
`(u8 *) prev + prev->size == (u8 *) blk`, computed as pointer-sum equality, and the merged size is
the **sum of both sizes**, not the block's own.

## func_80052874 — mode machine, decoded only

Open and decoded to the dispatch (see the previous record): mode machine on `D_8008A9FC`,
init arm clears `D_800B13DC` (0x90 bytes), stores 0 into `D_800B134E`, clears `D_8008A9F4` and
`D_8008B454`, calls `func_8005CBD8(0)` and `func_8005CBEC(7, 0, 0)`. Not drafted this pass.
Turn-on: `beqz $v1, .L80052934` at 0x800528A4 — a `switch` on `D_8008A9FC` whose case order must
come from `jtbl_*`, not from the arm order in the listing.

## State

- attempted 2 (one worked through the flag, one drafted), converted 0, parks 3
- pipeline: `scan` 684 files 0 problems, `gate` 684/684, `build` OK
- worktree check: 684 local = 684 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 684 merged; narrowed sweep open set 5, image body now
  at 125/151 with the flag on
