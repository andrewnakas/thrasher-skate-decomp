# func_80047C94 second attempt, 2026-10-28 (x)

Conversions 0, bodies attempted 1, parks 1. The pass went to the 151-word store-first body and
did not close it; the two larger members (169, 231) were not drafted.

## func_80047C94 — 151 words, 146/151, size 0x284 want 0x25c

Three shapes applied this pass, each measured:

| shape | result | what it fixed |
|---|---|---|
| header struct padded to 0x28 (`pad24[4]`) | 146/151 (unchanged count, frame 0x60) | `addiu $a0, $sp, 0x10` now matches — the name block sits at 0x10 below the header |
| `name` declared before `hdr` | 146/151 | same, made the block order right |
| single shared `return 0` (the memcpy loop moved into the `else`) | 146/151 | nothing measurable |

**The residue is now three named things, not ten:**

1. **The entry guard is one test, not two.** The game's `beqz $s1` / `blez $a0` at
   0x80047D58/0x80047D60 test the destination and the count *once* before the loop; the draft
   re-tests the count at the top of the loop (`blez $a1` at 0x80047D6C). The source shape wanted
   here is the count in a register that survives the guard, i.e. `n` computed into the same
   register the guard tests — a naming order problem, not a control-flow one.
2. **The parameter homes are shifted by one.** The game holds a0/s2, a1/s5, a2/s1; the draft holds
   a0/s0, a1/s4, a2/s1. Same class as the twins: the copy order at entry decides it.
3. **Ten words over** live in the unpack loop's per-iteration `4` scaling, which the game folds
   into the walking pointer `v1` advanced by `addiu $v1, $v1, 0x4` in the branch delay slot.

Turn-on instruction for the next attempt: `addu $v1, $s2, $zero` at 0x80047D70 — the source
walks one pointer for the source and one for the destination and derives the destination offset
per element, rather than indexing both.

## The two larger members

Not drafted. `func_80015A94` (169) has been decoded to line 0x80015B20: entry guard on a count
(`a0`), the block address `D_8008AD38 - (a0 << 4)` compared against `D_8008AD3C`, one-byte
presence check, three calls, then a `memset` of the freed block and a **three-way sorted insert
into a free list keyed by address with `D_8008AD4C` as the head and `-1` as the sentinel** — the
insert is the part that needs a careful pass, and it is where a first draft would park.
`func_80052874` (231) was not opened.

## State

- attempted 1, converted 0, parks 1
- sweep conversion rate: 1 of 3 narrowed-list bodies attempted has converted (33%); of the whole
  lane, 3 conversions in the last 6 passes
- pipeline: `scan` 684 files 0 problems, `gate` 684/684, `build` OK
- worktree check: 684 local = 684 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 684 merged; narrowed sweep open set still 5
