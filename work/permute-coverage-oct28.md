# Pass record — permuter aimed at compiler-output parks

## Operators now cover liveness and pressure, not just order

`work/permute_search.py` (still one file, still scoring through `tools/match.py:compare`):

| family | operators |
|---|---|
| order | swap two declarations, swap two statements, move a declaration anywhere in the body |
| types | retype a local (`u32/s32/u16/s16/u8/s8`), cast a right-hand side, `+=` ↔ `x = x + y`, swap addends |
| liveness / pressure | typed alias of a value used once (`T2 y = (T2) x;` + rename), alias inserted at a chosen later use, extra temporary introduced and used, temporary merged back, expression split into two statements, copy moved to a different point, copy dropped |
| control flow | `if (c) { v = K; } return v;` ↔ `if (c) { return K; } return v;` (moves a value's last use across the guard) |

Two modes: random walk (accept improvements, 5% plateau moves) and `--exhaustive`, which scores
the *whole* single-mutation neighbourhood each round in parallel (`--jobs`), keeps the best and
repeats (`--rounds`). Both stop on `--seconds`, `--max-compiles` or a `--stall` of compiles
without improvement.

## Results per body (provably compiler output: no `$at` value temps, no `t0..t3` load walk, no GTE)

| body | base | best reached | variants scored | what stopped it |
|---|---|---|---|---|
| func_80034C8C | 3 words, size exact | 3 (no move) | 88 exhaustive | needs `addu $a2,$v1,$zero` where we emit `nop`: a copy gcc only creates when the value has a reason to live twice. Every alias/copy spelling coalesces. |
| func_800382C0 | 6 words, size exact | 6, register agreement 4 → 5 | 46 × 2 exhaustive | the only difference is where `lui/ori 0x1E000` lands. Backend scheduling of a constant pseudo; no source position changes it (named local hoists it, inline literal moves the value to `$v1`). |
| func_800337C4 | 16 words, size −1 | 16 | 20 exhaustive | the missing `addu $v0,$a0,$zero` before the twelve stores. `return m`, `r = m`, int cast, copy-pointer stores — gcc coalesces every one. |
| func_80035BC0 | 21 words, size −1 | 14 | 81 × 3 exhaustive | two redundant `andi $x,0xFF` after `lbu`s; the source masks must come from something gcc cannot bound, and the grammar has no "widen the value's known range" move. |
| func_80033818 | 12 words (all names) | no move | 5,601 + 3,357 random | **not C**: hand-written `t0..t9` register walk (proved by synthetic compile + 0/653 merged units) |

Total this pass: ~380 exhaustive variants plus the earlier 11.5k random ones. **0 conversions.**

## What the search cannot express (the useful part)

1. **A copy that must survive.** gcc 2.8.1 coalesces any pure copy, so `q2 = q;` never produces
   the game's extra `addu`. The grammar can insert aliases but they all fold. Reaching
   `func_80034C20`/`func_80034C8C` needs a construct where the second value has a *different*
   reason to exist (e.g. two lvalues the compiler must treat as distinct) — no operator models
   that, and the two parks have now survived hand shapes, random search and exhaustive search.
2. **A constant's materialisation point.** `func_800382C0` differs only in where `lui/ori` sits.
   That is a backend choice about a constant pseudo, not a source-order property; every operator
   either hoists it or moves the *value* instead.
3. **Range knowledge.** `func_80035BC0`'s residue is two `andi`s that appear only if gcc cannot
   bound a value. The grammar can add `(T)` casts but cannot make a byte load look unbounded.

Also found and fixed while aiming the tool: the line grammar assumed one statement per line, and
several of the saved parks put four stores on a line, so their neighbourhoods were nearly empty
(20 variants instead of hundreds). Normalising a draft to one statement per line before permuting
is now part of using the tool.

## Queue and pipeline

Queue: **361 unmatched bodies** (`work/enumerate.py`, current `origin/main`). Pipeline on a fresh
branch from `origin/main`: `scan: 656 files, 0 problems` · `gate: 656/656 — GATE PASS` ·
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)` · `objdiff: every unit file is a
100% match`.
