# Pass oct29a — volume on untouched bodies, no hypothesis to test

Tree `7605c52b` (693 units, matches `origin/main`). Upstream had moved from `5e7ecd3` to `7605c52`
since the last pass: it merged `#209` (`func_80027880`), `#210` (the selector change set) and five
other units (`func_8001C4BC`, `func_8002221C`, `func_8002C8B8`, `func_8003834C`, `func_80038A80`).
The tree was fast-forwarded before any draft, and the selector re-synced.

## Selection

`select.py list --fresh` returns **20 bodies**, and the smallest is **119 words** — everything below
that is now merged, attempted, not-C, or closed-by-evidence. With no small band left, the pick was made
on structure rather than size: leaf bodies (no call signatures, no argument homing) and one call-heavy
body, since call sequencing is the class that has converted here.

| body | words | frame | shape | why picked |
|---|---|---|---|---|
| `func_80020608` | 135 | 0 | leaf, no calls, 8 loops | no frame, no signature to get wrong |
| `func_8002ECB8` | 119 | 0x38 | 5 calls + list walk | smallest fresh body |
| `func_8003031C` | 127 | 0xB8 | 11 calls, 2 matrix builds | call sequence, the proven class |
| `func_8002D330` | 143 | 0x30 | leaf, mult/mflo | no calls, single switch |

## Per-body numbers

| body | shape | size | matching | residue |
|---|---|---|---|---|
| `func_80020608` | pointer walk | 108/135 | 0 | 27 short |
| `func_80020608` | index form + `D_80092CB4` | 118/135 | 1 | 17 short |
| `func_80020608` | byte-offset form | 119/135 | 0 | 16 short |
| `func_8002ECB8` | pointer walk | 118/119 | 8 | 1 short |
| `func_8002ECB8` | countdown loop + `k` local | 121/119 | **23** | 2 over |
| `func_8003031C` | direct | 127/127 | **81** | 46 differ |
| `func_8003031C` | `-fno-strength-reduce` | 127/127 | **87** | 40 differ |
| `func_8002D330` | direct | 96/143 | 0 | 47 short |

## Verdicts

**`func_80020608` — parked, address folding.** All eight loop bodies reproduce exactly (link loop 12
words, clear loop 10). The whole deficit is that the game keeps a *running byte offset* in one register
and adds the table base every iteration (`addu $v0,$v1,$t9`, fields at `3/0x28/0x2C`), while gcc 2.8
folds base into the induction variable (`addiu $v1,$t3,0x28`, fields at `-0x25/0/4`). Three spellings —
pointer, index, byte offset — all fold; the byte-offset form is the closest at 119/135.
Turn-on: `0x80020684` (`addu $v0,$v1,$t9` against our `addiu $v1,$t3,0x28`).

**`func_8002ECB8` — parked at 23/119, 2 words over.** Closest body of the pass. The prologue, the
`memset` guard, both `func_8002F054` walks and the slot countdown all reproduce; forcing the compare
constant into a local made gcc keep it in `$s6` across the call exactly as the game does
(`sw $s6,0x30` appeared, +2). What is left is the tail: the game shares the epilogue
(`beq $a0,$v0,.L8002EE6C` with `addu $v0,$s4` in the delay slot), ours emits `bne`+`nop`+`j`+delay.
Turn-on: `0x8002EE4C`.

**`func_8003031C` — parked at 87/127, best of the pass.** 81 words matched on the first compile and
the per-file `-fno-strength-reduce` took it to 87, confirming the banked rule that the flag restores the
game's positive displacements — the loop went from `0x48/-0x4` back to `0x44` on the base pointer.
The remaining 40 are homes and call setup: the game keeps the second matrix address in `$s0` and passes
it with `addu $a0,$s0`, where ours re-materialises `addiu $a0,$sp,0x40`; the table base costs one extra
`addu`; and `lh $s2,0x28` vs `lh $v0,0x28`.
Turn-on: `0x800303A8`.

**`func_8002D330` — parked, 47 short.** The three-axis switch and the `mult`/`mflo` products do not
survive transcription: gcc reorders the difference computations and drops the write-only stack slots at
`0x10..0x28` that the game keeps. Not a shape guess — the body needs the local record the listing writes.
Turn-on: `0x8002D3FC`.

## Count

conversions **0**, bodies attempted **4** (8 measurements total), parks **4**. No PR: nothing matched.

Queue at `7605c52b`: 318 open, 236 attempted, 693 merged units.
