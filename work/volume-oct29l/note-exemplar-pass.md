# Exemplar-first selection — 52 candidates, two bodies drafted, two skipped as not C

Method: for every open, unattempted, non-retired listing of 40–200 words, intersect its `D_`/`func_`
symbols with each merged unit's symbol set and rank by overlap; read the top exemplar's source before the
listing, then copy its declarations, pointer spellings and call setup. 52 candidates had a
symbol-sharing exemplar.

## Skipped without measuring — not C

| body | why |
|---|---|
| `func_8003B60C` (52 words) | `/* Handwritten function */`, `cfc2 $t4,$27` — no C spelling |
| `func_80049F54` (80 words) | `/* Handwritten function */`, `mtc2`/`mfc2`/`ctc2`/`gpf 1` (GTE) |

## Drafted whole, measured once each

| body | exemplar | result | first divergence |
|---|---|---|---|
| `func_8002103C` (160 words) | `func_800212BC` | **2 of 160 words match, size 0x264 vs 0x280** | `0x8002103C`: frame `0x40` vs `0x48`; the exemplar's `func_80020C34(a,b,c,&sp18,&sp1C,&sp20)` and the `D_8009C6D4` removal loop were copied verbatim, but the 3 stored locals plus 2 outgoing words did not land, so seven words are missing before the first store |
| `func_8004C3A4` (136 words) | `func_8004C5C4` | **26 of 136 words match, size 0x22c vs 0x220** | `0x8004C3A8`: `s7 = a1, s4 = a0` in the game, `s6 = a0, s4 = a1` in the draft — argument home, and three words over |

Both drafts are saved: `work/best/func_8002103C.c`, `work/best/func_8004C3A4.c`.

## What the exemplars bought and did not

The exemplar copy did work at the *statement* level: `func_800212BC`'s `func_80020C34(…, &sp18, &sp1C,
&sp20)` setup, its `D_8009C0A4[D_8008A2A4++] = id;` and its whole `D_8009C6D4` removal loop reproduced
without a spelling search, and `func_8004C5C4`'s `func_80051574`/`func_80051728`/`D_8008B424` 0xFF-walk
copied into the `0xC0` arm unchanged. What it did not buy is the part that decides these bodies: which
callee-saved register each argument lands in (`s6`/`s7` vs `s7`/`s4`), and the frame extent that follows
from the stored locals. Both are the home class this lane cannot name in C — the same wall as the
previous fifteen passes, reached faster and with an exact first-divergence instruction instead of a
fifteen-shape search.
