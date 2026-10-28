# Freshness-aware selection and two framed-band drafts, 2026-10-28 (d)

Branch `freebuff/records-oct26`. Tool change on `freebuff/lane-select` (PR #196).

**Conversions: 0. Attempts: 2 framed-band transcriptions + 1 refused candidate.**
Queue unchanged: 676 merged / 406 open.

## The guard now knows what "fresh" means

`lane/select.py` reads attempt state out of the records branch (`origin/*/records-*`, newest by
commit date; `--records` / `LANE_RECORDS_REF` to override) and classifies every open body:

| state | rule | behaviour |
|---|---|---|
| merged | `src/funcs/<name>.c` exists | never listed, never drafted |
| attempted | a path under `work/` on the records branch names it | listed with its best recorded `N/M`; `check` and `draft` refuse it when the intent is fresh |
| fresh | neither | the only thing `list --fresh` prints |

Proved on the two bodies that caught the previous pass and one that has never been drafted:

```
REFUSED (intent fresh) func_8002AC14: ATTEMPTED — best 76/86 — work/best/func_8002AC14-s1.c
REFUSED (intent fresh) func_8002B674: ATTEMPTED — best 37/37 — work/census-corrected.md
OPEN func_80049F54: FRESH, 80 words, absent from main@ebba874e
select: REFUSED func_8002BCF4: ATTEMPTED — best 12/28 — work/census-corrected.md
select: fresh ground was asked for; pass --allow-attempted to re-test a park
```

A markdown record only counts as evidence when its line also carries a `work/` path, an `N/M` residue
or a `not C` verdict — otherwise `work/census-corrected.md`, which lists the whole queue, would have
marked every body in the project attempted (558 of 682 on the first attempt; 293 with the rule).

`list --fresh` also drops listings whose first line is `/* Handwritten function */`. That mattered
immediately: the two freshest-looking candidates in the band, `func_80049F54` and `func_8003C77C`,
are GTE bodies (mtc2/mfc2/mvmva) that nobody had drafted *because* they are not C. `check` now refuses
them as `HANDWRITTEN`.

Result for the 70-110 word band: 41 open → **33 fresh C bodies**, 199 attempted, 676 merged.

## Drafts

| function | words | best | residue class | turn-on instruction |
|---|---|---|---|---|
| `func_8002CE0C` | 83 | 71/83 (0x148, want 0x14C) | frame content — an extra saved register | `sw $s3,0x1C($sp)`: our draft needs four saved registers where the game needs three, because the two sum temporaries stay live across `func_8002CF58`; and the table index became `sllv` off a hoisted `1` that gcc CSE'd with the `sa = 1` literal |
| `func_8002E8E0` | 84 | 67/84 (0x12C, want 0x150) | loop rotation and induction form | `lw $v0,0x0($t1)` at 0x8002E924: the game duplicates the list test at top and bottom with `addiu $t1,$t1,0x4` in each delay slot; ours rotates to a single test behind a `j` |

Both prologues came out exact under prologue-first, including `func_8002E8E0`'s unusual order
(`s1`/`s0` initialised from the two symbol addresses *before* the `jal`, `s3 = a0` in its delay slot).
What `func_8002E8E0` needed and got from a banked rule: reading `a0+2`/`a0+0xA` inline instead of in
hoisted locals — the "base pointer re-loaded before every use" rule — which moved it 82/84 → 67/84
and fixed the frame from 0x20 to the game's 0x28.

## Rule check

`sltu` again wants an unsigned operand: `func_8002E8E0` compares `s2 >= d1` with `slt` where the game
has `sltu`, so the squared distance is a `u32` in the source. That is the second confirmation of the
narrow/unsigned-operand rule, and it is the cheapest untried change on that draft.
