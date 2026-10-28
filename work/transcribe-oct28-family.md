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

## Queue, and a counting defect that bit this pass

361 at pass start. #170 and #172 merged during the pass (`c84bc0b`, `d06cb36`); #171 is still open.
Measured on the records branch after fetching: **360** unmatched bodies now, **359** when #171 lands.
`scan.py` 0 problems, `gate.py` 657/657, `build.py`
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)` on every branch that was shipped.

**The count is not reproducible from `origin/main`.** `work/drafts.py` and the rewritten
`enumerate.py`/`verify.py` are tracked only on `freebuff/records-oct26` (PR #148, still open). `git switch
-c <lane> origin/main` deletes `work/drafts.py` from the working tree, so `work/enumerate.py` run on a
fresh-main branch either dies on the import or silently reports a different queue (379 in one run here,
against 360 with the tooling present). That is the same defect the mission has flagged for several passes
and it cannot be fixed from this lane: it needs #148 merged, or `work/*.py` added to main by the
maintainer. Until then every pass must count from the records branch and say so.

## Second sweep: the leaf sibling next door

`func_80056F4C` (42 words, no frame, no call) has a draft in `work/best`; re-measured it rather than
redrafting. `work/best` base: 18/42, 0xa0 vs 0xa8. With `/* cflags: -mno-split-addresses */` it reaches
19/42 at 0xa4 — the copy loop (four `lw`/four `sw` per 0x10, `bne` on the end pointer) matches word for
word, so the struct assignment `*dst = D_800B2428[D_8008B4DC[0]]` is confirmed as the source shape.

Residue, named: the game materialises the flags word as `lui %hi(D_800B29DC)`, `addiu %lo`,
`addiu v1,v1,-0x4D4`, then `lw/sw 0x4D0(v1)` — i.e. `D_800B29DC - 4`, split across two statements. Every
spelling tried (`Tbl *t = (Tbl *)((u8 *)D_800B29DC - 0x4D4); t->flags`, a `u8 *fl` intermediate, the
plain folded form) makes gcc fold `-0x4D4 + 0x4D0` into one `%lo` of `0x800B2508`, which also costs the
word. Remaining diff is that fold plus the `lui` of the copy base sitting after the slot guard instead of
in its delay slot, plus `andi $a0` vs `andi $v1` on the slot mask. Parked as address-fold + slot fill.

## Next batch

The family's other members are all heavier (saved-register frames, 45-102 call sites): func_8005458C,
func_80054BF4, func_800558A8, func_80055D64, func_800566FC (2 calls, 9 s-reg uses — the closest),
func_800568C0, func_80056A64, func_80057FC4. func_800566FC is the one to open next: two calls and a
9-use saved set is small enough to keep the prologue readable.
