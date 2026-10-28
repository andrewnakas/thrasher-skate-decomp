# pass oct28y — func_80027880 closes: 3 of 135 → MATCH

The closest body in the lane, and the residue was four words wide once aligned.

## The three differing words, read from the alignment

All three sat in one rotation at `0x80027960`, at the head of the second list-append:

| address | game | ours |
|---|---|---|
| `0x80027960` | `lw $v1, 0x2C($s1)` — the entry's pointer | `sw $s1, %gp_rel(D_8008B024)` |
| `0x80027964` | `lw $a0, %gp_rel(D_8008B088)` — the current bound | `lw $v1, 0x2C($s1)` |
| `0x80027968` | `sw $s1, %gp_rel(D_8008B024)` | `lw $a0, %gp_rel(D_8008B088)` |

**Cause: ordering, not a home and not a missing instruction.** Every instruction is present on both
sides; the game reads the two operands of the first boundary fold *before* it stores the new list
tail, and gcc 2.8.1 would not hoist either load above the store when both lived inside one
expression tree printed after the store statement.

## The fix

Write the game's order literally: name the two operands in locals, then store, then fold.

```c
    {
        u32 q = *(u32 *) (e + 0x2C);
        s32 lim = D_8008B088;

        D_8008B024 = (u32) e;
        t = (*(s32 *) (q + 4) - (*(s32 *) (q + 0x10) >> 1)) << 16;
        if (lim < t) {
            t = lim;
        }
        D_8008B088 = t;
    }
```

`q` is used only by the first fold, so the five later folds still re-read `0x2C($s1)` as the game
does — the fix would have cost five words if it had been hoisted to function scope.

Measured once: `func_80027880: MATCH` (0x21C, 135 words). The tidy form (bound store moved inside
the block) re-matched, so the shipped C is the clean one, not the scaffolding.

## Verification and ship

- `scan.py` 688 files, 0 problems; `gate.py` 688/688; `build.py` `SLUS_009.35: OK`
  (`16829afba66533e2645bf87af2774671b06ff36b`) — identical image bytes with the unit in place.
- PR **#209**, single file `src/funcs/func_80027880.c`, cut from freshly fetched `origin/main`
  (`f41520e`) in a throwaway worktree, so the main tree never switched branches.
- The local draft was then removed from `src/funcs/` (unmerged upstream) and kept at
  `work/best/func_80027880.c`; the tree is back to 687 units.

## Selector fix shipped separately

PR **#210** (one file, `lane/select.py`) carries the change set that had been sitting uncommitted:
attempts reconciliation to `work/attempts.tsv`, the `closed` state, and the row-only harvest rule
that stops a body being retired by a mention in proof prose.

## Queue

`319 open`, `240 attempted` (the three drafts from the last pass are now recorded), `29 not C`,
`7 closed-by-evidence`, `96 recorded-but-merged`, `687 merged units`, tree at `f41520e5`.
`func_80027880` stays counted as attempted until #209 merges.

## Next closest, from the attempted table

`func_80032FF4` 12/13, `func_80033818` 12/13, `func_80032C28` 10/11, `func_800337C4` 16/16 — all
four are class-B home residues (identical sequence, different caller-saved register), so their
next shape is the entry-live argument test, not a spelling.
