# Pass: the argument tell, applied as a checker rather than a selector

Date: 2026-10-28. Second sweep of the register-home pool, this time reading every residue as a possible
missing call parameter before touching any spelling.

## Per-body table

| function | before | after | verdict |
|---|---|---|---|
| `func_80042E9C` | 2 of 58 | **MATCH** | an argument after all — `func_80032C54` takes the guarded field as arg 1 in `a1` |
| `func_80055820` | 1 of 34 | 1 of 34 | not an argument; naming the `0x3E8` constant does not move the materialisation out of the `jal` slot |
| `func_8003BF7C` | 2 of 79 | 2 of 79 | not an argument; the `lui` temp for the base of `D_8008ACA0` |
| `func_80056C90` | 2 of 36 | 2 of 36 | not an argument; `lui`/`addiu` split across two registers |
| `func_80020D74` | 4 of 39 | 4 of 39 | not an argument; `or` hoisted across a stack load |
| `func_8002050C` | 4 of 25 | 4 of 25 | not an argument; allocation at the join |
| `func_8003BDB8` | 6 of 31 | 6 of 31 | not an argument; allocation |
| `func_80057090` | 5 of 92 | 5 of 92 | not an argument; allocation |
| `func_800257A0` | 5 of 21 | 5 of 21 | not an argument; pointer copy hoisted over the loop guard |
| `func_8002F4C0` | fresh | 23 of 27 | block layout: the game puts the shared fail block *between* the guards and the compute |
| `func_80020570` | fresh | 30 of 38 | parameter/table register rotation, size −2 |
| `func_80058448` | fresh | 39 of 43, size −2 | gcc caches the address of a symbol the game re-materialises per use; costs a saved register |

Conversions **1 of 12**. Attempts: 12 (9 parks, 3 fresh).

## What the tell is worth

As a *checker* it is decisive and cheap: read forward from the guard, and if the argument register is not
rewritten before the next `jal`/`jalr`, the value is that call's argument. That cleared eight of the nine
parked rows in minutes and found the one that was real (`func_80042E9C`), and it is now four conversions
in two passes with no misses.

As a *selector* it is weak. `work/argprobe.py` flags every listing where a load into `a1`-`a3` is guarded
and still live at a call; over 409 open bodies it produced 11 hits, of which exactly one was a genuine
missing parameter. The other ten are argument registers that happen to hold a stale value at the call, or
guards whose register is reused for an unrelated purpose. Do not queue off the probe — run it as a
10-second check on any body whose residue is an argument register.

The one shape the tell still explains badly: `func_80055820`'s constant is a *legitimate* argument
(`func_800309C4(0x3E8, …)`) but the game materialises it twice — once in the `beqz` delay slot and again
after the intervening call — where gcc keeps it to one materialisation in the `jal` slot. Naming the
constant does not change it.

## Correction to #191

`func_80042E9C` has been removed from the issue's table: it was an argument, not allocation. The remaining
eight rows were each re-checked with the probe and none hit, so the class is now understated rather than
overstated — which is the right direction for a filing asking for a tool. Issue edited in place.

## Shipped

- `func_80042E9C` — PR #192, `scan.py`/`gate.py`/`build.py` green, image sha1 `16829afb…` unchanged.

## Queue

673 merged units on `origin/main` when the pass started, 674 with this unit in review; 409 unmatched
listings open.
