# pass oct28z — both twins matched and shipped

## func_80026478 — 4/177 → **MATCH** (PR #206)

The four remaining words were the address build, twice. Only one spelling produced the listing's
`addu $a0, $a0, $s2` + `addiu $a0, $a0, 0x48`:

| # | spelling | measurement |
|---|---|---|
| 0 | `&base[i1 * 140 + 0x48]` | 4/177 |
| A | `(u8 *)(0x48 + i1 * 140 + (s32) base)` — bias first | 151/177, 0x2c0 |
| B | `(u8 *)(0x48 + (s32) base + i1 * 140)` — bias and base swapped | 4/177 |
| C | named `u32 o1 = i1 * 140;` then `base + o1 + 0x48` | 8/177 |
| **D** | **`(u8 *)(i1 * 140 + (s32) base) + 0x48`** — index-left sum, base added before the bias | **MATCH** |

Shipped from `origin/main` at commit `6faecb6`, one file added; scan 686/686, gate pass, build
`SLUS_009.35: OK` on the branch.

## func_80026870 — 22/177 → **MATCH** (PR #207)

The address spelling took it from 26 to 22 in one step, and the remaining 22 were the first sign test
written from the wrong premise. In the twin the **negated component copies belong to the positive arm**,
not the negative one:

| arm | func_80026478 | func_80026870 |
|---|---|---|
| `r1 >= 0` / `r1 > 0` | plain copy, `s4 = r1` | negated copy, `s4 = r1` |
| the other | negated copy, `s4 = -r1` | plain copy, `s4 = -r1` |

Writing that arm order exactly gives **MATCH**. Shipped from `origin/main`, one file added; scan
686/686, gate pass, build `SLUS_009.35: OK` on the branch.

The lesson for the bank: the twins differ only in which arm carries the negation, and assuming the
"negative" arm negates is what cost 22 words on the second body.

## State

**Conversions 2 this pass** (both twins), plus `func_800250B4` from two passes ago now merged (the unit
count on main went 684 → 685).

Pipeline on the lane tree: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`.
