# Pass oct29f — the walker's two named residues, worked in order, then the permuter

One body opened, one body closed permanently. No new bodies, no flags, no tooling.

## `func_80034874` — 64 → 66 matching, exact size 129/129

Both requested changes were made, one at a time, so each number is attributable:

| step | change | matching |
|---|---|---|
| start | two ordering fixes from oct29e in place | 64/129 |
| 1 | constant materialised in the source before the locals are first touched (`lui $a1,0xE100` / `ori` wants to precede `addiu $a0,$sp,0x28` and the `$s2`/`$s6` initials) | **66/129** |
| 2 | `v == 0x20 || v == 0` split into two `if`s | 66/129 (null) |
| 3 | if/else chain with `c.n3++` placed so it is live across the first branch | 39/129 (worse) — reverted |
| 4 | best draft restored, then permuter budget | see below |

The prologue reorder is the only change that paid: +2 words, and it is the interleave the alignment
named (constant first, then the save band). Splitting `||` into two `if`s changes nothing at all, and
forcing the two-forward-`beqz` shape as an if/else chain costs 27 words — gcc then sinks the increment
arm out of line, which is the opposite of the shared arm the game has.

### Permuter: measured null on this residue

`tools/permute.py func_80034874 --run`, ~6,200 iterations, baseline score 1,155:

- best score reached **875** — a 24 % improvement in the tool's metric, never near zero;
- the winning variants are all prologue line permutations (`$s2`/`$s6` seeding, save order, constant
  slot), i.e. the tool is reaching exactly the scheduling residue the alignment names and cannot
  express the game's order;
- no output scored 0 and no variant would have changed the matching-word count materially, so nothing
  was read back — shipping a permuter shape that still differs is noise, not a unit.

Parked at **66/129, exact size**, draft `work/volume-oct29f/func_80034874-66of129.c`.
Residue: prologue constant/save interleave (`0x800348B0`) and an inverted branch pair at `0x8003494C`
(the game has two forward `beqz` to one shared block, ours `bnez` + `j`). Both are scheduling picks.

## `func_8003599C` — closed permanently

As instructed, not re-tested. Its five missing words are gcc cross-jumping the second dispatch's
`default` block into the first; no allowed flag disables cross-jumping, so it is not a shape C can
express. Turn-on `0x80035B90`. Recorded as class C in `work/closed-by-evidence.md` so `lane/select.py`
classifies it `closed` and refuses it from now on.

## Count

conversions **0**, attempts **1** (`func_80034874`), bodies measured **1** this pass (4 measurements on
it). No PR — nothing matched, and no unit file was written or overwritten: the draft lived at
`src/funcs/func_80034874.c` only while being measured and was moved to `work/` and deleted before the
records commit.

Queue: see `lane/select.py` census in the pass log; 693 units on `origin/main`, `src/funcs` clean.
