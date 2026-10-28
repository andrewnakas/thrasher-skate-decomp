# pass oct28y — the twin pair: duplicated copy per arm is the structural lever

## func_80026478 — 109/177 → **4/177**, size exact

The diagnosis in the oct28x record was right and the prescribed shape closed almost all of it. One
change did it: **every one of the three component copies is written inside each arm, not once before
them.** The game duplicates the copy into both branches of each sign test, which is what puts the
third store in the branch's delay slot and gives the body its 17 words.

| # | shape | measurement |
|---|---|---|
| 0 | single copy before the three tests (oct28x) | 109/177, 0x280 (17 short) |
| 1 | **copy duplicated into both arms of all three tests** | **8/177, size exact** |
| 2 | `&base[i1 * 140 + 0x48]` array-index spelling for the two record pointers | **4/177, size exact** |
| 3 | `i1 * 140 + base + 0x48`, then `&base[i1 * 140] + 0x48` | 8/177 each — reverted to 2 |

The remaining 4 words are one address build, twice: the game emits

```
addu  $a0, $a0, $s2      ; index + base
addiu $a0, $a0, 0x48     ; + bias
```

and every spelling tried emits the two operations in the other order, or with the `addu` operands
swapped. Five spellings are now eliminated with measurements; the residue is the fold order of the
constant bias in the address build, and the body is otherwise instruction-identical at exact size.

## func_80026870 — 26/177, size exact, parked

The twins differ in exactly one thing, and it is not a tag or an offset: the first sign test is
**inverted**. `func_80026478` has `bgez` (negative arm first), `func_80026870` has `blez` (positive arm
first), with `negu` and `addu` swapping arms to match. Everything else in the two listings is
byte-identical.

Substituting the flip (`if (r1 > 0) { plain } else { neg }`) gives **26/177, size exact** — the same
body, one arm polarity away. That is a real, cheap second body: it needs the `negu`/load interleave of
the negative arm matched, not a re-decode.

## State

Conversions 0, bodies attempted 2 (the repaired twin and its partner). Best drafts:
`work/best/func_80026478.c` at 4/177, `work/draft-80026870.c` at 26/177.

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
