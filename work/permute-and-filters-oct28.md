# Pass record — permuter built, specimen disproved, handwritten class landed

## The permuter exists now

`work/permute_search.py` — in-repo random-search permuter wired to the project's own matcher
(`tools/match.py:compare`), so every variant is judged by exactly the pipeline the gate uses.

```
python3 work/permute_search.py func_80033818 --src work/best/func_80033818.c --seconds 240
```

- Mutates: declaration order, statement order, local types (u32/s32/u16/s16/u8/s8), copy
  placement (`T x2 = x;` + rename, and the inverse), `+=` vs `x = x + y`, addend order, `(u32)`
  casts on right-hand sides.
- Score: `(words differ, |size delta|, -register agreement)`. The third term decodes the register
  fields of every word that differs and counts how many already agree, so a body whose only
  residue is register names is not a flat landscape.
- Keeps improvements, allows 5% plateau moves, writes `work/permute-work/<name>/best.c` and, on a
  match, `MATCH.c`. Budgets: `--seconds`, `--max-compiles`, `--seed`.

| body | compiles | result |
|---|---|---|
| func_80033818 | 5,601 + 3,357 | no improvement (flat even with the register term) |
| func_800382C0 | 2,551 | plateau 6 words / reg agreement 4 → 5, no match |

~11.5k scored variants, one plateau step, **0 conversions**.

## The "clean specimen" is not C: the 0x80033xxx copy family is handwritten

`func_80033818` was billed as instruction-identical with only register names differing. Its
listing walks `$t0,$t1,$t2,$t3,$t4,$t5`. A C 12-word copy does not: compiled through the pinned
pipeline a 12-word load/store copy emits `$2,$3,$6,$7,$8,$9,$10,$11,$12,$13,$14,$5` — gcc fills
low registers first and runs out of `t` registers on the last value. Proof is a synthetic
(`work/scratch2/synth_copy.c`, both a permuted 6-word copy and a straight 12-word copy).

Measured across the whole merged corpus: **0 of 653 merged units contain an ordered
`lw $t0 … lw $t1 … lw $t2 … lw $t3` chain**; 12 unmatched listings do
(`func_80032FF4`, `func_8003302C`, `func_8003353C`, `func_8003384C`, `func_80033A18`,
`func_80033BE4`, `func_80037070`, `func_8003DDAC`, `func_8001C540`, `func_80044E10`,
`func_80033818`, `func_80033E14`). That is the hand-written register walk, and those bodies leave
the C queue.

## Correction to last pass's `$at` claim

Last pass recorded "`$at` anywhere ⇒ handwritten". That is only half true, and the wrong half
would delete real work:

| `$at` form | merged C units with it | verdict |
|---|---|---|
| `lui $at, %hi(sym)` + `mem … %lo(sym)($at)` | 5 (`func_80011BD4`, `func_80011C40`, `func_8003ED28`, +2) | **compiler output** under the allowed `/* cflags: -mno-split-addresses */` (20 merged units carry a per-file cflag) |
| `slt $at, …` / `addu $at, …` as data temps | 0 | handwritten |
| `mult` + two or more `nop`s | 0 | handwritten (`func_80032C28`; its neighbour `func_800331FC` emits the same multiply block with no nops) |

## Filters landed in `work/enumerate.py`

Added `AT_VALUE` (value-temp `$at`), `MULT_NOPS` (hand-scheduled HI/LO padding) and
`hand_written_chain` (ordered `lw $t0…t3`). Queue: **375 → 364 bodies** with the same merged-unit
set. The address-form `$at` is deliberately **not** filtered.

## Flag axis measured (negative result)

`work/flag_sweep.py` runs every allowed per-file cflag over one draft. On `func_80033818` every
flag gives the same 12-word diff (`-O0` gives 63), so per-file flags do not move register choice
for a body whose instruction sequence already agrees.

## Conversions and queue

**0 from 12 bodies attempted** this pass. Last pass's two units merged (#167 `func_8001D804`,
#168 `func_8002BA64`), so current `origin/main` is 655 units, gate green, sha1
`16829afba66533e2645bf87af2774671b06ff36b`, objdiff 100%. With the new filters the queue is
**362 unmatched bodies** (was 376 before them).
