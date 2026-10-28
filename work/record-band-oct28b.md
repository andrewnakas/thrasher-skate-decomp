# Leaf-band pass, 2026-10-28 (b): volume with the two arm-polarity facts

Branch `freebuff/records-oct26`. Selection: unmatched, no `jal`/`jalr`, no coprocessor,
no `$at`, not marked handwritten — 64 bodies in the whole game range, i.e. the leaf well is
nearly dry and what is left is small and mostly already shaped.

## Conversion: func_8002DDE0 (14 words) — PR #181

Third shape. The listing's entry is `j <test>` with `addiu v1,v1,-0xC` in its delay slot, and
the loop has ONE epilogue shared by the found path and the fall-out. That is not a `for` with
the step in the increment clause (which emits a pre-check and two returns), and not a
`while` with the step in the body. It is the step inside the **condition**:

```c
p = D_8008B060;
while ((p -= 0xC) >= D_8008B05C) {
    if (*(u32 *) p == key) {
        return p;
    }
}
return 0;
```

New banked fact: **a `j` into the loop test whose delay slot carries the step means the step
belongs to the condition**; that is what rotates the test to the bottom and lets both exits
share one epilogue.

## Attempted, parked (6)

| body | words | best | class |
|---|---|---|---|
| func_80032C28 | 11 | 6/11, size 0x1c vs 0x2c | 64-bit pair extraction: `mfhi` before `mflo`; game also carries three mult-latency nops. Same blocker as the filed pair-order issue; no spelling reached it, union view included |
| func_80032FF4 | 13 | 12/13 | scheduler: game batches all six loads before the three adds and three stores; every source shape tried (direct, staged temps, add-then-store) folds back to the interleaved form |
| func_80033818 | 13 | 12/13 | scheduler, same latching: six pure loads then six pure stores |
| func_800337C4 | 16 | 16/16, size 0x3c vs 0x40 | delay-slot fill: ours puts the twelfth store in the `jr` slot, game leaves `nop`; one word |
| func_80011B48 | 17 | 13/17, permuter 8/17 (score 55) | commutative operand order: game emits `srl` before `sll` in one of two identical rotates; gcc canonicalises both to `sll` first from every spelling, and the permuter's best variant was assignment-as-expression noise |
| func_800257A0 | 21 | 15/21, size 0x58 vs 0x54 | address form: gcc biases the walk pointer to `a0+0x74` and uses negative displacements; the struct-index form lost the walk entirely (21/21, 0x5c) |

## Process defect, again

func_8001D804 and func_8002BA64 were decoded and drafted before checking them against
`origin/main`; both were already merged, and the drafts overwrote merged unit files in the
working tree. Caught, reverted with `git checkout --`, tree verified clean (664 files, no
`src/funcs` diff). The check must run over the whole candidate list at selection time, not on
the first batch only.

## Queue

`origin/main` today: 664 merged, **418 unmatched** of 1082 game functions; 417 once #181
lands. Leaf C-work (no call, no coprocessor, no `$at`, not handwritten): 64 bodies — the
leaf well is essentially exhausted, and every one of the 64 is in the classes above.

Pipeline green on the PR branch: scan 0/664, GATE PASS, BUILD PASS,
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.
