# Sweep list, first drafts, 2026-10-28 (viii)

Conversions 0, bodies attempted 2, parks 2. Short of the five-to-six target; the reason is in the
last section and it is not a tooling gap.

## What was worked

| function | words | best | residue | turn-on instruction |
|---|---|---|---|---|
| func_8004AC1C | 98 | 86/98 (0x178, want 0x188) | four words short; the refill loop's re-entry condition | `beqz $v0, .L8004ACE4` at 0x8004AD58 — the loop re-enters when `s0 >= e->unk2C` after the refill, and the `e->unk2C -= s0` tail is reached from both entries, so the loop and the tail share one exit |
| func_800380BC | 129 | 123/129 (0x1fc, want 0x204) | two words short; the memcard retry nesting | `bgtz $s1, .L8003818C` at 0x8003825C — the outer loop's advance (`s1 -= s0; s6 += s0`) sits *after* the inner retry exits, and the inner `s3 -= fp` retry rewinds the sector pointer |

Neither reached the store-first shape: `func_8004AC1C` has no store-then-branch of a call result
in its body, and `func_800380BC`'s only such site (`MemCardReadData` → `beqz $v0`) branches on the
result without storing it first. So the two smallest members of the sweep's list were not
store-first bodies after all — the scanner's signature is looser than the lever: it matches
"branch on the result", and the lever only bites when the result is *also* stored into a record
before the branch. That is worth knowing before the rest of the list is worked.

### Decode carried forward

`func_8004AC1C` is fully decoded: a 0x20-slot tick loop over `D_800AEA24[i]`, each item with a
sub-list at `unk38` trimmed by decrementing `unkC` and freeing entries whose count hits zero,
then a refill loop that consumes `unk30` against the `unk2C` budget through
`func_8004B4A8`/`func_8004B41C`/`func_8004B448`, invoking `rec.fn(&rec)` when the record carries
a hook at `+0xC`, and calling `func_8004AF80(i)` when the item's flags carry bit 4. The parked
draft is one shape away: the four missing words are the duplicated `e->unk2C -= s0` tail.

`func_800380BC` is also fully decoded — open the memcard, read 0x200, then an outer loop over the
name length (`s1`), an inner retry of at most two attempts that rewinds `s3` by 0x80 on failure,
`func_80034D4C` copying `s0` bytes from `D_800A812C` into the caller's buffer, and
`func_80037C20` returning the checksum byte compared against `D_800A812C[0x7F]`.

## Why only two

The sweep's list was enumerated last pass and is real (17 open). Working it, the two smallest
members turned out not to carry the lever at all, and both decodes are heavy enough that the
first transcription of each lands with a four-to-six-word structural gap rather than a near miss.
Drafting five of these in one pass is not a matter of trying harder with the current per-body
effort; it needs the decode of each written down once (as above) and then a *second* short shape
pass the following session. Both drafts here are exactly that starting point.

## State

- attempted 2, converted 0, parks 2 with turn-on instructions and full decodes
- pipeline: `scan` 683 files 0 problems, `gate` 683/683, `build` `SLUS_009.35: OK
  (16829afba66533e2645bf87af2774671b06ff36b)`
- worktree check: 683 local = 683 upstream immediately before the records commit
- queue: 141 open fresh, 219 attempted, 683 merged (two more merged upstream since last pass)
- sweep's list on this tree: 17 open, of which the two worked are now attempted → 15 remain
