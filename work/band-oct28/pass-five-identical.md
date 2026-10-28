# Pass: statement boundaries on the instruction-identical five (29 Oct 2026)

Population: the five open bodies that were already instruction-identical to the game except for which
register holds which value. Method: for each, name the value whose home differs, then split / name /
reorder the statements around it (types are exhausted); permuter with a short budget only where the
hand rewrite stalls, and translate its winner into clean C rather than shipping its noise.

Guard first: `select.py draft` now refuses a missing or unreadable `--src` with a one-line message
instead of a traceback (exit 1, nothing written). Everything below came from the synced tree.

## Conversions (1 of 5)

| function | result | PR |
|---|---|---|
| func_80011B48 | **MATCH** | [#195](https://github.com/andrewnakas/thrasher-skate-decomp/pull/195) |

Two statement-boundary changes, both readable:

```c
u32 rol = (s << 4) | (s >> 28);
u32 hi = s >> 16;          /* naming the two halves of the second rotate  */
u32 lo = s << 16;          /* pins srl before sll, as the game emits it   */
u32 z = rol + (hi | lo);
...
return D_8008AC84 = (z << 16) | (z >> 16);   /* store and return in one statement */
```

The merged single-expression form (`(s >> 16) | (s << 16)`) leaves exactly two words different: gcc
swaps the two shifts. Splitting them into named statements fixes the order. The merged store-and-return
is what puts the result in `$v0`; a separate `D_8008AC84 = z; return z;` does not.

The permuter's score-0 winner contained `| (D_8008AC84 << 16)` — a redundant re-read of the global,
which got the score but is not what the source needed: with the shifts split, the clean single read also
scores 0. Translated, not shipped as found. Verified: match, scan 675/0, gate 675/675, build
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.

## Parks (4), each naming the instruction its claim turns on

| function | words | residue | turns on |
|---|---|---|---|
| func_80033818 | 13 | instruction-identical, register names only | `lw $t0,0x4($a0)` — game's first temp is `$t0`; ours `$v0`, then `$v1,$a1,$a2,$a3,$t0` |
| func_80032CF4 | 18 | instruction-identical, register names only | `srl $t0,$a0,30` — game `$t0`; ours `$v0` (q in `$a2` vs `$v0`, rem `$v1` vs `$a3`) |
| func_80032D3C | 19 | same body, `>>16` — converts with CF4 or not at all | as above |
| func_80033E14 | 25 | instruction-identical, register names only | `lw $t0,0x0($a0)` — game `$t0…$t9,$v0,$v1`; ours `$v0,$v1,$a2,$a3,$t0…` |

Statement splitting does **not** move these four: `func_80032CF4` with `top`/`twoq`/`t` broken out is
byte-identical to the unsplit draft (q still `$a2`, rem still `$v1`). `func_80033E14`'s permuter run
improved 120 → 60, but every winning variant is a *store reorder* (`dst[5]` moved after `dst[9]`), which
is score noise, not a register change. `func_80033818` ran flat at 60 for the whole budget.

So the lever that converted 80011B48 is real but narrow: it moves a register only where the *value's
definition* is what gcc is choosing between (two shifts it could order either way, a store whose result
must also be the return). Where the value is one of N interchangeable loads, statement order does not
reach the allocation.

## Queue

`origin/main` at `0e9a9f57` (two lane PRs open on top): **674 merged unit files, 408 unmatched listings
open.**
