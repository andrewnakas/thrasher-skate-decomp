# Pass: smallest open bodies against a fixed checklist (28 Oct 2026)

Method asked for: walk the smallest open bodies in ascending size, each a short job against a fixed
checklist — frame/save set, argument check from the guard forward to the next call, banked facts in a
fixed order, one measurement, park on the allocation class. Also: permuter sweep over parks at exactly
one differing word.

## Headline

**14 bodies attempted, 4 of them already merged on main (stale), 10 genuinely open, 0 conversions.**

The stale four are the lane's recurring defect and this time they were four of the fourteen:
`func_8002BCB0`, `func_8002FE80`, `func_8002DDE0`, `func_80035BC0`. All four were picked off a base
branch cut before their merges. The check that would have caught it — `git cat-file -e
origin/main:src/funcs/func_XXXXXXXX.c` over the *whole* list before drafting — was run only after the
drafting was done.

## Per-body verdicts (open bodies only)

| function | words | result | residue / class |
|---|---|---|---|
| func_80032C28 | 11 | 10 of 11 vs game (size 0x20 want 0x2c) | 3-word mult latency pad (#76) + `mfhi` before `mflo` (#179) — both filed |
| func_80032FF4 | 13 | 12 of 13 | scheduler: game keeps all 6 loads above the first store, we sink a[1]/a[2] below it |
| func_80033818 | 13 | **instruction-identical, register names only** | allocation (see below) |
| func_800337C4 | 16 | 16 of 16 | gcc coalesces the return copy into the base (stores via `v0`, game stores via `a0`) + delay slot |
| func_80032CF4 | 18 | **instruction-identical, register names only** | allocation |
| func_80032D3C | 19 | **instruction-identical, register names only** | allocation (same body as CF4, `>>16`) |
| func_80043294 | 17 | 14 of 17 | `D_800AAB94 + 0x780` folded into one reloc where the game adds `0x780` separately; pointer/counter homes swapped |
| func_80011B48 | 17 | **instruction-identical, `$v0`/`$v1` swapped only** | allocation (two-register case; 3 expression orders tried, no move) |
| func_80033E14 | 25 | **instruction-identical, register names only** | allocation, sharpest specimen (below) |
| func_80032D88 | 17 | 17 of 17, size 0x3c want 0x44 | clamp compare form (`slti` vs `slt at,-1`) + duplicated `sra` |

Six of ten open bodies are instruction-identical to the game and differ only in which register holds
which value. That is the wall, and it is now the majority of what this size band contains.

## What the checklist steps actually paid

| step | bodies where it applied | conversions |
|---|---|---|
| frame / save-set read first | 4 (all framed) | 0 — none of the framed bodies had a frame error |
| argument check, guard → next call | 3 open bodies | 0 this pass |
| banked facts in fixed order | 10 | 0 |
| `-mno-split-addresses` | 2 | 0 alone, but **2 of 2 reproduced the game's address form** |
| strength-reduce flag (largest displacement, negative offsets) | 0 | no body in the band needed it |
| permuter at one differing word | 2 parks | 0 |

## New facts

1. **`-mno-split-addresses` reproduces the split *address* form, not just global stores.** On
   `func_80032D88` and `func_80043294` the flag turns `lui %hi; addiu %lo; addu` into the game's
   `lui $at,%hi(sym); addu $at,$at,index; lh/sw %lo(sym)($at)`. The flag's documented use
   (`func_80011BD4`, `func_80011C40`) was stores to globals; it applies to any leaf that builds a
   table/record address from an index. Two bodies now hold that shape; it should be tried on the
   address-form population by default, not after a failure.

2. **Two of the "allocation" residues were missing call parameters, and one was the condition-step
   loop.** Recovered from the merged C on main for three of this pass's stale candidates:
   - `func_8002FE80`: `func_8002FEE0(self, buf)` — the buffer address is an argument, which is why the
     game keeps it in `$a1`. My draft missed the second parameter and sat 1 word off (`$v0` vs `$a1`).
   - `func_8002BCB0`: `D_8008A318(t->f18, n)` — the tested field is also the second argument, which is
     why the game loads it into `$a1`. My draft sat 2 words off on exactly that.
   - `func_8002DDE0`: `while ((p -= 0xC) >= D_8008B05C)` — step inside the condition, which is what
     produces `j .test` with `addiu` in the delay slot instead of a rotated loop. My draft rotated.

   So the argument rule and the condition-step loop form were both live in this band and I parked
   three bodies without applying them. That is the process error of the pass, not a compiler limit.

3. **The free-register order differs from the game's.** `func_80033E14` (12 temporaries, no call, so no
   argument explanation possible) shows our cc1 allocating `$v0,$v1,$a2,$a3,$t0…` while the game uses
   `$t0…$t9,$v0,$v1`. `func_8002FE80` chose `$v0` where the game chose `$a1`; `func_80011B48` chose
   `$v0` where the game chose `$v1` for the first of two temporaries. This is a property of the
   allocator's preference order, not of liveness, and no statement-order or declaration-order mutation
   tried this pass moved it.

## Permuter

Two runs, both timeboxed, both flat:

- `func_80032CF4` (instruction-identical, 16 words by name): base 145, 1292 iterations, never below
  145; 26 accumulated errors from degenerate mutations. Killed at the 8-minute bound.
- `func_8002BCB0` (1 real word, base score 10): 7 minutes, no output below 10.

Alongside the earlier passes this makes the tool's measured record: it has never converted a body whose
residue is a register home. It converts only when the residue is a *shape* the mutator can reach.

## Queue

`origin/main` at `73b95a4`: **674 merged unit files, 408 unmatched listings open.**
