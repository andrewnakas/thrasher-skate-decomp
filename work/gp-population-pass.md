# The gp-address population pass, 28 Oct 2026

Method: open each body with the frame read off the listing (prologue-first), then apply the proven split
spelling — symbol declared one byte, address taken into a pointer local, displacement applied at the use —
then the banked levers. Whole-body transcription, one measurement, cap a few shapes, park at single-digit
scheduler residue.

## Conversion: 1

| body | words | how it closed |
|---|---|---|
| **func_80024F3C** | 50 | first transcription 24/50 differing and 1 word long; the `n` local for the table index removed (inline `D_8008A2BC` in the subscript) took it to 14; declaring both record indexes **before** the first store (`a`, `b`) took it to **2**; the permuter closed the last two `addu` operand-order words in 136 iterations. Shipped as PR #176 on `freebuff/gp-sweep`, from fresh origin/main: `MATCH`, `scan` 661 files 0 problems, `gate` 661/661, `build` `SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`. |

That is the first conversion this lane has had in five passes, and the second time the permuter has closed a
2-word allocation residue — it is the right tool for exactly that size, not for 7-9 words.

## Parks, with the class named

| body | words | residue | class |
|---|---|---|---|
| func_8002050C | 25 | 7 words: `sll` before `addiu $gp`, `-1` materialised twice instead of copied | scheduler / constant materialisation |
| func_800190E0 | 76 | 9 words: same `sll`/`addiu` order, `andi` home `$v1` vs `$a0`, loop-init order | scheduler / register home |
| func_80025004 | 44 | 42/44 and 4 words long: four index loads not pipelined ahead of the stores, `addu` order | scheduler / load order |
| func_8004A094 | 39 | 40/39 and 2 words long: base hoisted into a fifth saved register | allocation (frame) |

Permuter budgets spent: 80024F3C 136 iterations to zero; 8002050C 420 s (best 475, base 670);
800190E0 420 s (best 180); 80025004 420 s (best 790). Only the 2-word body converged.

## New levers, both proved on the shipped unit

1. **Declare every record index before the first store that uses one.** With the indexed stores written
   inline in order, gcc interleaves each `lw` with its store and pads 4 extra words (0xc0 vs 0xb0); naming all
   the indexes up front pipelines the loads exactly as the game does (0xb0 exact).
2. **Inline a gp-relative table index instead of caching it in a local.** func_80024F3C went 24 → 14
   differing words when the `n = D_8008A2BC` local was removed and the global was subscripted directly; the
   local was costing a register and a reload pattern the game does not have.

## Population

110 unmatched listings carry an `addiu $x,$gp,%gp_rel(S)` address; 58 were open against fresh origin/main,
all of the ≤22-word members already merged. This pass worked the 24-50 word band of that open set.

## Queue

Fresh `origin/main` after this pass's unit merged: 662 merged units, clean enumerator **355** unmatched
bodies, 185 of them never drafted (357 before func_80024F3C and one other unit landed).
