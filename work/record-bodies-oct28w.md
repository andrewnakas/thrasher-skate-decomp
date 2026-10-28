# pass oct28w — the two proved classes retired, four bodies measured

## 1. Bookkeeping: closed-by-evidence

`work/closed-by-evidence.md` already carried both classes with their benches. What it did **not**
carry was a body-level row for every retirement, and `lane/select.py` harvested *every* address in
the file — including the two twins, which appeared only in class B's proof prose. They were saved
from a wrong retirement only by being merged; a prose mention must not close a body.

Fixed:

- `closed_set()` reads table rows only (`^\| `func_XXXXXXXX` \|`). Prose is evidence, not retirement.
- `func_8001A710` got its own row under B, so it stays retired now that prose no longer counts.

Counts before → after the fix: 7 → 6 → 7 (the row restored it).

| class | bodies retired | closing evidence |
|---|---|---|
| A elided entry copy | `func_8004ADA4`, `func_8002E4B4` | `work/bench/copy_probe.py`, 16 spellings: only the 64→32 widen→narrow emits the pair, and it pays `sra` ×2, frame `0x20` (want `0x18`) and an extra save — applied to the real body 96/119 → 119/119 at size `0x1e4` vs `0x1dc` |
| B caller-saved home | `func_8002050C`, `func_800382C0`, `func_8003012C`, `func_8003B3CC`, `func_8001A710` | each reached exact size with the value in the wrong class of register; no spelling in C names a home (`oct29`/`oct30` measurements in the file) |

Selector now: `7 closed-by-evidence`, and `check` refuses them with `CLOSED BY EVIDENCE`.

**One new datapoint for class B, from this pass** (worth the row, not a re-test): three untouched
leaf bodies — `func_80032FF4`, `func_80033818`, `func_800337C4` — compiled to the game's exact
instruction *sequence* and differed only in which caller-saved register homes each value:

| body | game | ours | order |
|---|---|---|---|
| `func_80032FF4` (13 w) | six loads in `$t0..$t5` | `$v0,$v1,$a1..` | identical |
| `func_80033818` (13 w) | `$t0..$t5` | `$v0,$v1,$a1,$a2,$a3` | identical |
| `func_800337C4` (16 w) | const in `$t0`, base `$a0` | const `$v1`, base `$v0` | first word swapped |

A `$t0`-first allocation with `$a0` still the base means the four argument registers were already
live at entry — i.e. the game's body names parameters the draft does not (the `read signatures
forward` lever), or the allocator's order differs. Neither is a spelling, so all three park as
class B with the turn-on instruction being **the destination of the first load**.

## 2. Four bodies, one measurement each

`--fresh` is empty: every open body has a path under `work/` on the records branch. The smallest
open bodies are what remains, so they are what got drafted.

| body | words | result | residue and turn-on |
|---|---|---|---|
| `func_80032FF4` | 13 | 12/13 | identical sequence, homes `$v0,$v1,$a1..` vs `$t0..$t5`; turns on at `0x80032FF4` (first load's destination). Class B |
| `func_80032C28` | 11 | 10/11, size `0x20` vs `0x2c` | 64-bit `>>16` is the right shape (`mult`, `mflo/mfhi`, `srl`, `sll`, `or`) but gcc emits no mult-latency nops and reads `mfhi` before `mflo`; turns on at `0x80032C2C` where the game has the first of three `nop` |
| `func_80033818` | 13 | 12/13 | six-load/six-store rotate reproduced in the game's order; homes differ. Class B, same turn-on |
| `func_800337C4` | 16 | 16/16, size `0x3c` vs `0x40` | constant 3×4 store plan is right, but gcc copies the base to `$v0` first (`addu` at word 0) where the game does `lui` then `addu`; turns on at `0x800337C4` |

Conversions **0**; bodies attempted **4** this pass (plus the three carried over from the
interrupted pass, now measured: `func_8002F52C` 128/129, `func_8002D56C` 113/114,
`func_80027880` **3/135** — the closest thing in the lane and worth the next pass's first slot).

## 3. Queue

`319 open` (0 fresh: all recorded), `237 attempted`, `29 not C`, `7 closed-by-evidence`,
`96 recorded-but-merged`, `687 merged units`, tree at `f41520e5`.
