# The clamp idiom benched, and the small fresh band that turned out not to be C, 2026-10-28 (h)

Tree cut from `origin/main@aa8fe7a6` (680 units) with `lane/select.py sync`; worktree checked before and
after every branch move with the inline equivalent of `verify` (main still has no `verify`).

**Conversions: 0. Attempts: 1 framed body + 4 small bodies classified.**
Queue: **680 merged on main + 2 in review (#199, #200), 401 open**.

## The bench

Twelve clamp spellings, compiled through the real pipeline (`tools/cc.py c ... --print-asm`), against the
game's nine-word block from `func_80039BB4`:

```
sltiu v0, v1, 0x200      ; v0 = x < 0x200   (unsigned)
beqz  v0, L1
sltiu v0, v1, 0x201      ; v0 = x <= 0x200  (unsigned, in the delay slot)
blez  v1, L2             ; x <= 0 (signed)
L1: bnez v0, L3
j L3 ; addiu a0, zero, 0x200
L2: a0 = 0
```

| # | spelling | words | shape |
|---|---|---|---|
| v1 | `if (a > hi) a = hi; else if (a <= 0) a = 0;` | 10 | `slt`/`bne` (signed), hi arm via `j`+`li` |
| v2 | helper with both bounds (not inlined, call) | 8 + call | not comparable: emits a `jal` |
| v3 | `(a < hi) ? ((a > 0) ? a : 0) : hi` | 9 | `slt`/`beq`, `bgez`, keep in `$2` |
| v4 | explicit `u32 u = (u16) a;` + if/else-if | 11 | `sltu 0x201` first, so the `x < hi` test disappears |
| v5 | arms assign into one result variable | 10 | same as v1, extra `addu` to the result register |
| v6 | macro `((x) > hi ? hi : ((x) <= 0 ? 0 : x))` | 9 | `beq`+`bgtz`, keep in `$2` |
| v7 | early returns | 8 | `beq`/`blez`, no join — wrong for a caller that continues |
| v8 | bounds in a local (`hi = 0x200`) | 11 | constant hoisted to a register, no immediate form |
| m2/m6 | nested `if ((u32) x >= hi) { if ((u32) x > hi) x = hi; } else if (x <= 0) x = 0;` | **8** | `sltu`+`bne`, `sltu 0x201`+`bne`, `j`+`li`, `bgtz`+`addu` |
| m5 | two sequential ifs: `if ((u32) x < hi) { if (x <= 0) x = 0; } if ((u32) x > hi) x = hi;` | 9 | `sltu`/`beq`, `bgtz`, zero inline, then **recomputes** `sltu 0x201` |
| t2/t4 | `if ((u32) x < hi) { lo } else if ((u32) x <= hi) {} else { hi }` | 8 | same multiset as the game, all three branches inverted |
| m3/m4 | unsigned parameter / ternary with casts | 7-11 | both fold the second compare away |

**Verdict: no spelling reproduces the game's block exactly.** The game needs three things at once that the
compiler will not give together: the `x < 0x200` test branched *to the hi arm* (`beqz`), the zero arm placed
*after* the hi arm and reached by `blez`, and the `x <= 0x200` result reused by that zero arm — i.e. the
compare computed once and consumed across a block boundary the game has reordered. `m5` computes the right
number of compares but recomputes the second one after the store; `m2/m6` and `t2/t4` produce the identical
instruction multiset in 8 words with every branch polarity inverted. That is a block-layout decision, the
same class as the delay-slot fills already filed, not a source shape. Applying `m2/m6` to `func_80039BB4`
anyway took it from 76 to 81 words (0x144 against 0x168) and 88 → 87 differing words: correct direction,
not a conversion.

## Small fresh band: four bodies that are not C

`lane/select.py list --max 83 --fresh` offered, smallest first: `func_80011B3C` (3 words), `func_80027538`
(27), `func_80023B1C` (35), `func_80032E94` (40), `func_80033268` (49), plus my unmerged `func_8004B088`.

| function | words | verdict |
|---|---|---|
| func_80011B3C | 3 | **not C** — `config/functions.us.csv` already marks it `kind=data`; the selector's fresh list should exclude non-`func` rows |
| func_80027538 | 27 | **not C** — stores `$sp` into `0x1F8003FC-0x14` and reloads it into `$sp`; a stack-pointer swap is not expressible in plain C |
| func_80023B1C | 35 | **not C** — same manual `$sp` swap plus five arguments parked in gp globals around it |
| func_80032E94 | 40 | **not C** — the function calls but has no frame and parks `$ra` in `$t7` across the `jal`; also uses `bgez $zero` as an unconditional branch |
| func_80033268 | 49 | **not C** — same `$ra`-in-`$t7` pattern, no frame |

So the sub-84 fresh band is not work: it is four hand-written bodies and one data symbol. The next real
volume below the worked size starts at 83-84 words, i.e. the band already being worked. That is worth
recording as a selection rule: the fresh list must be filtered on the listing (frame + `$ra` handling +
`$sp` arithmetic), not only on `kind`.

## Worktree

```
$ for f in $(git ls-tree -r --name-only origin/main -- src/funcs); do [ -f "$f" ] || echo MISSING $f; done
(no output)
$ ls src/funcs/*.c | wc -l ; git ls-tree -r --name-only origin/main -- src/funcs | wc -l
680 / 680
```

Pipeline green at 680: scan 680 / 0 problems, gate 680/680, build PASS
`16829afba66533e2645bf87af2774671b06ff36b`.
