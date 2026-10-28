# func_800294FC — deep pass, 2026-10-28

Body: 90 words (0x168), `a0`/`a1` -> `func_8001D5B0` key, builds a 0x1C-stride record array from a
0x18-stride source array, four walking pointers.

## What the listing says (read instruction by instruction)

```
prologue 0x294FC..0x29574  (31 words)
  a3 = a0; v1 = D_8008A088; if (v1 != 0xFFFF) skip init
     D_8008ADB8 = D_8008C45C; D_8008ADBC = 0x6040; if (0x6040 < 0x16A8) D_8008ADBC = 0x16A8
  src  = func_8001D5B0(a0, 0x53565053, 1)          -> s0
  out  = func_80034C20(src->count * 0x1C)          -> t0
  g    = D_800A4F00 (lui v0 / addiu v1) ; *(g+0x54) = out ; t3 = g      ** addu t3,v1,zero **
  i    = src->count - 1 (reload; nop in the load slot) ; bltz i, end
     sp = (u8*)src + 0xC          (t1, built IN the bltz delay slot)
     a3 = (u8*)src + 0x12         ; a2 = out + 4
loop 0x29578..0x29650 (55 words)
  out->f1 = sp[0] ; out->f2 = *(u16*)(sp+2)
  v = *(u16*)(sp+4) ; if (v) w = g[0x54] + v*0x1C - 0x1C else w = 0 ; out->f4 = w
  v = *(u16*)(sp+6) ; same                                                  ; out->f8 = w   (store in the bnez delay slot)
  kind = dp->f4 ? 0x70 : (t ? 0x70 : 0x6C)      (lw of f4 from memory, bnez / bnez / j, 10 words)
  for (j = 0; j < 4; j++) out->w[j] = *(u32*)(sp + 8 + 4j)   (sltiu, a0 = sp copy, v1 = out copy)
  step: a2 += 0x1C ; t0 += 0x1C ; a3 += 0x18 ; i-- ; bgez ; sp += 0x18 (delay slot)
```

## Combination table (measured, `match.py`)

| # | out access | src access | f4/f8 arm | kind arm | result |
|---|---|---|---|---|---|
| A | index (`out[i]`) | index | `w=0; if (v) w=…` + 1 store | ternary | 63/90, size 0x160 |
| B | walking `dp++` | walking `sp += 0x18` | if/else, store per arm | ternary | 71/90, 0x164 |
| C | walking | walking | if/else assigning `w`, 1 store | ternary | 71/90, 0x158 |
| D | walking | walking | C + `u32 j` (sltiu) | ternary | 71/90, 0x158 |
| E | walking | walking | C | `dp->f4 ? 0x70 : (t ? 0x70 : 0x6C)` | 71/90, 0x158 (gcc canonicalises; identical words) |
| F | walking | walking | C | `(dp->f4 \|\| t) ? …` | same, `beqz` polarity |
| G | walking | walking | C | if / else-if / else with store per arm | 58/90, 0x164, **two `sb`** (game has one) |
| H | walking | walking | C | `k = 0x70; if (!f4 && !t) k = 0x6C; dp->kind = k` | 71/90, 0x158, `bnez` polarity ✓ |
| I | walking | **`sp` initialised in the for-init clause** | C | ternary | **71/90, 0x158** — best |

I is the best draft (`work/best-294FC-v3.c` is C; I is that plus the for-init move).

## New banked lever (proved by emitted assembly, this body)

**Initialise the walking source pointer in the `for` init clause, not before the loop.** Moving
`sp = (u8*)src + 0xC` into `for (sp = …, i = src->count - 1; i >= 0; i--)` changed three words at once:

- the pointer build moved from right after the `jal` into the `bltz` delay slot, exactly where the game has it;
- the pointer took `$t1` and the countdown took `$t2` (game's assignment), from `$t2`/`$t1`;
- the loop step came out in the game's order `a2, t0, a3, i--, bgez, sp += 0x18(delay)`.

Before this, `dp++; sp += 0x18;` at the end of the body produced `a3, sp, a2, i, bgez, t0`.
The declaration order of the locals was also permuted (7 orders) and changed nothing — gcc 2.8.1 numbers
temps by first use, not declaration.

## Remaining structural difference: 4 words (86 emitted vs 90)

1. **`addu t3, v1, zero` (prologue).** The game builds the base into `$v1`, stores through `0x54($v1)`, then
   copies `$v1 -> $t3` for the loop. We build straight into `$t3`. Two separate address builds were tried
   (the folded `%lo(+0x54)` form is worse: it loses the displacement entirely).
2. **`nop` in the count-reload slot** — the game reloads `src->count` *after* the global store; we hoist the
   reload above it, which fills the load slot with the address build.
3. **kind block, +2 words.** The game lays out the true arm as fall-through (`bnez` for the second test,
   `addiu v0,0x70` in its delay slot, `j`, `addiu v0,0x6C`, and a *second* `0x70` materialisation at the shared
   label) — 10 words. Ours lays the false arm out first (`beqz`, no jump) — 8 words. Eight spellings of the
   same value (rows E–H) all produce the 8-word layout; gcc only emits the 10-word one when it does not
   cross-jump the shared store.

Items 1 and 2 are allocation/scheduler; item 3 is branch layout for an equal-cost two-way test. All three are
backend, so the body is parked with class **backend: address-materialisation copy, load-delay nop and
branch-arm layout (4 words)**, not with a structure problem.

Permuter: not run. Rule in the record is 1–2 differing words; this sits at 4 words of *size*, which no
mutation changes.

Reproduce with: `cp work/best-294FC-v3.c src/funcs/func_800294FC.c` then
`python3 - <<'EOF'` moving `sp = (u8 *) src + 0xC;` into the for-init (see lever above).
