# func_80022F24 close-out and the rotation band, 2026-10-28 (c)

## Conversion: func_80022F24 (56 words) — PR #182

The 1-word residue was closed by the **permuter** in 146 iterations (base score 160 → 0),
after three hand shapes failed. The winning mutation is one line of real C, not noise:

```c
    i = 0;
    if (*(u32 *) (s + 0xFF8) == i) {     /* compare the count against the counter, not 0 */
        return;
    }
    ...
    } while (++i < *(u32 *) (s + 0xFF8));
```

**Fact: when a zero-guard and a `do/while(++i < …)` share the counter, compare the count against
the counter variable, not the literal 0.** That is what gives the counter the game's register and
puts the record advance in the switch arms' jump delay slots with the counter increment at the
test, instead of the reverse (one word and the whole allocation).

**Permuter rule, now measured:** at 45 differing instructions spread over one word of size, the
permuter converted in 146 iterations. The three earlier failures were at 7+ words of size. Hand it
one-word residues; do not hand it seven.

## Rotation band (single `j` into the test), 2 attempted

| body | words | shapes | best | class |
|---|---|---|---|---|
| func_800294FC | 90 | index form, then pointer-walk form | 63/90 at 0x160; 71/90 at 0x164 (want 0x168) | structure, two words short: the record loop's four walking pointers and the `(f4 \|\| f8) ? 0x70 : 0x6C` tag are decoded, but the pointer/index mix still differs |
| func_80035D2C | 69 | decoded only | — | not drafted: the default arm's table index (`a1+7` vs `a1*3`) is unresolved in the listing |

Drafts: `work/band-oct28/func_800294FC-s2.c`, `work/band-oct28/func_80022F24-s3.c`.

## Queue

`origin/main` (`e24a78f`, #180 and #181 merged): **665 merged, 417 unmatched**; 416 once #182
lands. Records: this file. Pipeline on the PR branch from `origin/main`: scan 0/666,
GATE PASS (666/666), BUILD PASS, `SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.
