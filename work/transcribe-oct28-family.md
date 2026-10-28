# Whole-body transcription, the D_800B2428 switch family (28 Oct, pass 2)

Mode: plain transcription of the pairing-free population, whole body first, measure once, correct only
what differed. Queue at pass start: **361** unmatched bodies (`work/enumerate.py`).

## The pairing-free population is now five bodies

`enumerate.py --limit 400` (unstarred) filtered to no `jal`, no `$s*`, no `sw $ra`, no `$sp`, no
coprocessor, no `$at` data temporary leaves exactly five, i.e. the fifty-odd leaf bodies earlier passes
worked are all drafted now:

| words | body |
|---|---|
| 86 | func_8002AC14 |
| 92 | func_80055FC4 |
| 115 | func_80047834 |
| 117 | func_80056104 |
| 135 | func_80020608 |

The three that converted this pass are three of the five; the family they belong to is below.

## Per-body verdicts

| body | result | residue for the parks |
|---|---|---|
| func_80055FC4 | **MATCH** (PR #170) | — |
| func_80056104 | **MATCH** (PR #171) | — |
| func_800562A8 | **MATCH** (PR #172) | — |
| func_8001C4BC | parked | 20/33 words, size exact; `pa`/`pb`/`ea`/`eb` land in a rotated register set (`a3/a2/v0/a0` vs the game's `t0/a3/a2/v0`) and the `*b` load is hoisted two slots early. Permuter: 400 compiles, no move. Allocation. |
| func_8002DA40 | parked | 32/33; identical op sequence but the next axis's `lh (r+0xC)`/`lh (r+0xE)` sit after the `bgez` in ours and before it in the game, so the body is 2 words short whatever order the statements are in. Scheduler placement. |
| func_8002C0B8 | parked | 26/36, size 2 words long; `lw (s+0x10)` is sunk below the `subu` in every spelling (inline, `w` local, two locals up front). Same scheduler class. |
| func_80047A44 | parked | 22/34, size exact; pure register homes (`len` v1/t2, `p` t0/a3, `i` t1/t0) after the types were fixed (`s32` loads give the game's `slti`/`blez`). Allocation. |
| func_8002AC14 | parked | 0x154 vs 0x158; the game subtracts `0x80` per channel *inside* the inner loop and ours hoists it to the prologue, and the `mult` operand order follows (`mult t7,t0` vs `addiu a1,t7,-0x80; mult a1,a2`). Loop-invariant motion, not source shape. |

## The family and the levers it proved

`D_800B2428` is an array of **112-byte** records indexed by the **gp-relative byte** `D_8008B4DC`
(`(idx*8 - idx)*16`); byte `+0x61` is a 12-way style/format switch. Remaining undrafted members that
mention the pair: func_8005458C, func_80054BF4, func_800558A8, func_80055D64, func_800566FC,
func_800568C0, func_80056A64, func_80056F4C, func_80057FC4 (func_80056FF4 has a draft in `work/best`).

Four levers, each proved on a shippable unit:

1. **One accumulator plus `break`, never `return` per arm.** `return <expr>` in each arm makes gcc
   duplicate `jr $ra` per arm. `u32 ret = 0; switch (...) { case 0: ret = ...; break; ... } return ret;`
   reproduces the single `v0 = ret; jr $ra` epilogue (func_80055FC4, 80 words → MATCH in one shape).
2. **Re-index inside every arm.** When the listing repeats the whole
   `lui/lbu/addiu/sll/subu/sll/addu` scale at the head of each arm, the original indexed the array by the
   global at every use. Hoisting a `u8 *p = base + idx*112` local collapses that to one scale and is
   wrong; `D_800B2428[D_8008B4DC].fNN` in each arm is right.
3. **Do not name a loaded field that is only tested.** func_80056104 sat at 26 words, all register names,
   with `v = r->f50;` and `(v >> n) & 1`. Dropping the local and writing `(r->f50 >> n) & 1` moved the
   accumulator from `$a0` to `$v1` and matched: the CSE temp carries the load, the named local does not.
4. **Nested `if`s with an arm-level `ret = 0`, not guard-and-break.** `ret = 0; if (a) { if (b) {
   ret = ...; } }` puts the zero in the first `beqz` delay slot exactly as the game does
   (func_80056104, 3 words recovered, size exact); `if (!a) { ret = 0; break; }` does not.

Lever 3 is the generalisation of the copy lever: the CSE temporary's home is decided by whether the
value has a name. Where a park's residue is "our value is in `$aN`, the game's is in `$vN`" and the value
is a single load read once per arm, try removing the local before trying anything else.

## Queue

361 at pass start; three units shipped as #170, #171, #172 → **358** unmatched bodies once they merge
(pipeline green on each branch: `scan.py` 0 problems, `gate.py` 657/657, `build.py`
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`).
