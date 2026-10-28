# The switch family, second sweep (28 Oct, pass 3)

Mode: enumerate the family, draft in confidence order against the four recorded levers, measure once,
correct only what differed. Queue at pass start: **361** unmatched bodies; **358** at the end of the
first sweep's merges (#170, #171, #172 all landed).

## Family census (unmatched bodies that mention the pair)

`D_800B2428` / `D_8008B4DC` appear in 13 unmatched listings. Only four of them actually switch on the
record's `+0x61` field, which is the template's signature:

| body | size | calls | s-regs | template member? |
|---|---|---|---|---|
| func_800566FC | 0x1A0 | 2 | 9 | yes — switches on `+0x62` inside a `+0x61`-derived record |
| func_80056A64 | 0x200 | 2 | 27 | yes |
| func_80055D64 | 0x260 | 1 | 31 | yes |
| func_80056324 | 0x3D8 | 3 | 80 | yes |
| func_80057CA4 | 0xB4 | 0 | 0 | **converted** — table lookup, not a switch |
| func_80057B94 | 0x110 | 1 | 19 | adjacent — bit-test query on the 48-byte sub-table |
| func_80056FF4 | 0x9C | 0 | 0 | adjacent — the other half of func_80056F4C |
| func_800568C0 | 0x17C | 3 | 38 | adjacent |
| func_800579E0 | 0x1B4 | 1 | 17 | adjacent |
| func_80056F4C | 0xA8 | 0 | 0 | adjacent (parked last pass) |
| func_8005458C / func_80054BF4 / func_800558A8 / func_80057FC4 | — | 29-102 | 0-90 | heavy |

So the template's own members left are four bodies of 104-246 words, each with calls and a real frame.
The cheap members of this family are now all converted or parked.

## Conversions

| body | result | how |
|---|---|---|
| func_80057CA4 | **MATCH** (PR #173) | whole-body transcription; 5 words wrong on the first measure, all in the base materialisation |
| func_80057B94 | parked | see below |
| func_800566FC | parked | see below |
| func_80056FF4 | parked (re-measure) | see below |

## Levers proved or corrected

1. **Materialise the table base in its own statement before scaling the index.** func_80057CA4 written as
   `D_800B2428 + idx * 112` emits the `sll/subu/sll` scale first and the `lui/addiu` after; the game has
   them the other way. `u8 *base = D_800B2428; u8 *p = base + idx * 112;` matches exactly. Same fix had
   already converted func_80057CA4's sibling shape — this is the second body the split-base spelling has
   landed, so it belongs next to the four switch levers.
2. **Invert the callee test to get the fallthrough right.** In func_80057B94 the game's
   `beq $v0,4 -> later` means the *lookup* is the fallthrough: writing `if (callee() != 4) { lookup }
   else { base }` moved the body from 61 to 41 differing words in one step. The `==` form puts the then
   block inline and costs a jump.
3. **A `switch` whose arms only test bits needs a result variable, not a return per arm.** func_80057B94
   from 41 → 27 differing words when the four arms became `r = ...; break;`-style assignments with one
   `return r` (here written as an `if/else if` chain with `r = 0` first, which is what the game's
   `1, 0, 2, 3` compare order implies).

## Parks, with the class

- **func_800566FC** (0x1A0): 84/104, 7 words long. First loop: gcc bakes `+0x14` into the walking pointer
  (`a0 = p + 0x14`, then `0x4(a0)`/`0x0(a0)`) where the game keeps one pointer and uses offsets `0x18`
  and `0x14`, and the `obj[0x63]` branch is laid out the other way round. Second loop: our six
  `rec->f4C |= mask` arms each store inline, the game cross-jumps them into a single shared
  `sw 0x4C(a2)`. Scheduler/cross-jump, not source shape.
- **func_80057B94** (0x110 exact): 27/68 after five shapes, all register names — the three saved params
  land `s0,s2,s1` instead of `s0,s1,s2`, and the result accumulates in `$a0` and is copied to `$v0` where
  the game writes `$v0` directly. Permuter: 637 compiles, no move. Allocation.
- **func_80056FF4** (0x9C): 2/39 — the `%hi(D_8008B4DC)` temp lands in `$v0` where the game uses `$a0`,
  one `lui` plus its `lbu`. Permuter: 300 compiles, no move; inlining the index and hoisting the slot
  local both leave it at 2. Allocation, one instruction pair.

## Tooling: the count is reproducible from main again

`work/drafts.py` existed only on the records branch while `work/enumerate.py` and `work/verify.py` on
main were the older globbing versions, so a branch cut from main lost the tooling. PR #174 adds exactly
those three files to main, nothing else. Verified on that branch (clean `origin/main` plus the three
files): `work/enumerate.py` prints **358 bodies**, the same number the records branch computes after the
three merges, and `work/verify.py` runs and reports an empty draft corpus rather than failing on the
import. Once #174 merges, a fresh clone can reproduce the queue count without the records branch.

## Queue

361 at pass start; **358** measured with `work/enumerate.py` on a branch cut from the current
`origin/main` (all of #170, #171, #172, #173 merged). The number has not moved between the run before
#173 merged and the run after it, even though `drafts.merged_bodies()` does contain func_80057CA4 and
659 unit files are on main; I could not reconcile that one-body drift inside this pass, so treat 358
as the measured figure and the exact per-body accounting as still owed. The `--limit` listing prints
194 rows for this queue, so the header total is coming from a different path than the rows and that is
where the next check belongs.
