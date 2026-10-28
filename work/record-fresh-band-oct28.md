# Pass: pair-order handoff, then fresh ground (28 Oct)

## 1. The handoff is filed

Issue **#179** — "Pinned cc1 extracts 64-bit multiply pairs high-word first; the game is
low-word first" — with the three evidence blocks: the exhaustive merged-unit sweep (all 647 units
compiled, **zero** emit any `mflo`/`mfhi` adjacency), the eight bench shapes (all high-first, flag
variants included), and the raw pre-maspsx cc1 listing against the game's func_80032C28. It names
the two protected paths that could fix it (`toolchain/maspsx` post-pass, or a `compiler.toml` pin
revisit) and is cross-referenced from a comment on **#76** (the missing 3-nop pad — the other half of
the same body's delta) and cites **#17** for the scheduler class. No protected path was edited.

## 2. Fresh ground: one body, close but parked

`func_8002C284` (71 words, 0x11c, recursive tree emitter with one self-call): first transcription
reached **20 of 71 words differing with the size exact**, in three shapes.
Best draft `work/best/func_8002C284-s2.c`.

Two tells came out of it:

- **`(s16)(a + b) << 16` makes gcc load `lhu`, dropping the cast makes it load `lh`.** When the
  result of a 16-bit add is immediately shifted left 16, gcc knows only the low half matters and
  picks unsigned loads; the game's `lh` proves the original summed in `s32` and shifted the sum.
  Reversing that cast moved the body from 23 to 21 differing words and fixed two loads.
- **Control-flow polarity of a two-sided range test**: `if (v >= 0x101) { ...; return; }` followed by
  the middle band reproduces the game's `bnez` fall-through; writing the same thing as
  `if (v < 0x101) { middle }` gives `beqz` and the wrong block order (41/71 vs 20/71).

Parked class: **cross-jumping**. The game merges the two identical `recurse(child); return;` tails
into one block at 0x8002C364 and jumps to it from both range branches; our gcc duplicates the `jal`
at each site, which shifts every downstream branch displacement by 4-5 words.

## 3. Queue and projection

Fresh `origin/main` 7e24509: **663** merged units, clean enumerator **354** unmatched.

| size band | bodies |
|---|---|
| ≤ 39 words | 55 |
| 40-79 | 99 |
| 80-139 | 93 |
| 140+ | 107 |

Drafted (marked `*`): 170. **Never drafted: 184**, and every one of those is ≥ 45 words — the small
and no-call bands are exhausted (the only undrafted no-call bodies are 3-4 word stubs and six
86-143 word ones).

Where the 354 are stuck, from this lane's measurements:

| class | reachable from C? |
|---|---|
| register allocation / save-order residue | yes in principle; permuter plateaus, ~40 bodies measured at 3-15 words |
| scheduler / delay-slot ordering | no — #17 documents it; ~30 bodies |
| 64-bit pair order (`mflo`/`mfhi`) | **no — #179, protected path; 6 bodies** |
| `mult` latency pad | **no — #76, protected path; same 6 bodies** |
| address materialised without a symbol | **no — #101, protected path; 1 body (func_80034B98, matches already)** |
| narrow-parameter mask form | **no — #46, protected path; open-ended count in the framed band** |
| handwritten (scratchpad stack, `$gp`/`$at` chains, `t7` return) | not C; ~66 excluded by the enumerator |

Honest projection: the immediately draftable fresh ground is the 80-139 and 140+ bands (200 bodies),
all framed and call-bearing, where prologue-first plus the banked levers apply but the residues land
in allocation or cross-jumping. Of the 354, roughly **13 are blocked outright by protected paths**
(pair order, pad, symbol, mask) and cannot be closed from `src/funcs/`; the rest are unwritten C.

## 4. Count

Attempted this pass: the handoff issue, and 1 fresh body (func_8002C284, three shapes).
Converted: **0**. Queue unchanged at 354.
