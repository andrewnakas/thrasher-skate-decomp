# Layout-first batch, 28 Oct (pass 22)

The lever this pass is **reading the operand pattern off the listing before writing any C**, so a
draft starts from what the compiler emitted instead of from what the surrounding code suggests the
record looks like. `work/layout.py` owns that reading (`verify.py` still owns every number,
`enumerate.py` still owns which bodies are open).

    python work/layout.py func_8002DE18     # one body's pattern
    python work/layout.py --scan            # unmerged, undrafted bodies with a direct symbol pair

## What the extractor reports

For a listing it prints: frame size and the prologue's save order, every memory access with base
register/displacement/width, the strides it can derive **from the emitted `sll`/`addu`/`sll` chain**
(not from a C type), every `andi` mask and every constant in materialisation order, every register
copy (`addu $d,$s,$zero`), and how each symbol is reached — `direct-pair`, `symbolic-load`,
`folded+0xN`, `$at`, or `gp_rel`.

Validated against the body that proved the tell last pass:

```
func_8002DE18  frame=0x0  saves=-
  symbol   D_8006F834     direct-pair
  symbol   D_8008B060     gp_rel+lw, gp_rel+sw
  sw   $a0  +0x0    base=$a1  w=4
  lw   $v0  +0x8    base=$v0  w=4
  copy     addu $a1,$v0,$zero   (insn 2)
```

which is exactly the C that matched: gp pointer, direct symbol pair, a copy of the old pointer, and
the field at `+0x8` — all read, none guessed.

## The population, counted

`--scan` reports **100 unmerged, undrafted bodies that materialise a symbol as a direct pair**
(99 after this pass's draft of `func_8004E330`, which the scan then correctly stops offering), i.e.
where lever A (incomplete-array extern, address materialised once) is the spelling the listing
already shows. Largest pair counts: `func_800309C4` (11), `func_8001B238` (9), `func_8004691C` (9).

## The batch, scored before shaping

`work/similar.py` ranks each candidate against the merged units:

| body | words | pairs | copies | nearest merged twin | score |
|---|---|---|---|---|---|
| `func_8004E330` | 76 | 4 | 7 | `func_8004E460` (50) | 0.317 |
| `func_80057E9C` | 74 | 3 | 4 | `func_800366F0` (26) | 0.280 |
| `func_8001B238` | 92 | 9 | 1 | `func_8004D820` (47) | 0.302 |
| `func_8003599C` | 137 | 5 | 2 | `func_8004D820` (47) | 0.261 |

Low scores: none of these is a template twin, so the probe carried no C skeleton and each draft had
to come from the extracted layout alone. The 40-70 word band is fully drafted, so 74 words is the
smallest undrafted ground that exists.

## Per-body verdicts

**`func_8004E330` — 2 shapes, 54/76, size `0x12c` vs `0x130` (one word short).** Layout read off the
listing: frame `0x28`; fifth argument is a **byte** read from `0x38($sp)`; table `D_800B03C4` walked
with a 2-byte stride and its `.b1` used as an index into `D_800AFCA4` with stride `0x4C`
(`(x<<2+x)<<2-x<<2`); the signature is `(handle, a1, a2, a3, u8)` with `(s16)` on `a1` and `(s8)` on
`a3` at the calls.

The residue is one scheduling decision: the game retires `sw $v0,%lo(D_80082948)($s1)` **before** the
`jal func_8004DEBC` and leaves a `nop` in the slot, while this build fills the delay slot with that
store and everything after shifts by one word. That is the recorded scheduler class (issue #17), not
a source shape; the epilogue fix that did move the body (single `return 0` with the body inside
`if (handle != 0)`, instead of an early return) is banked for the next body.

**`func_80057E9C` — layout decoded, not drafted.** 74 words, three `sprintf` paths. Extracted pattern:
`multu` by `0x10624DD3` + `mfhi` + `srl 6` (unsigned `/ 1000`), the remainder rebuilt as
`v0 = v1<<5; subu; <<2; addu; <<3` (= `1000 * q`), a 16-bit `andi 0xFFFF` on each part, and two
thresholds — `sltiu 0x3E8` and `sltu 0xF423F` (999999). Signature: `(u32 value, u8 *buf)` writing one
of `D_8008AC68`, `D_8008AC6C`, `D_8008AC74`. The association step (`v1` from the second division, `a3`
as the middle part) is what a draft has to get right; it is transcribed here rather than guessed at.

**`func_8001B238` — not drafted.** It owns rodata (a `dlabel` pair at `D_80010668`/`D_8001066C`), so a
unit file would carry the function's own rodata; that is legal but it needs the table contents copied
exactly, which is a different job from the layout read.

**`func_8003599C` — not drafted.** 137 words; the pair count is high but the twin score is the lowest
of the batch, and a 137-word body is past the size where a first transcription has ever landed here.

## Conversions

**0 converted, 2 drafted fully measured, 2 analysed with their layouts extracted.** Queue unchanged.

## Pass 23 — transcription: one shipped unit, one park

No new tooling. Worked the bodies whose layouts were already decoded, whole-body first.

**`func_80057E9C` (74 w) — MATCH, PR #161.** Started from the layout written down last pass and went
55 → 54 → 58 → 64 → 14 → 0 words in five measurements. What each step turned out to be:

| shape | words | what it fixed |
|---|---|---|
| first cut (`total = value / 1000`, `sec = total - min*1000`) | 73, size `0xf8` | nothing: one division where the game has two |
| `ms = value % 1000; total = (value - ms) / 1000` | 58, `0x10c` | the second division (`multu` appears twice, as in the game) |
| `sec = total % 1000` | 64, `0x11c` | wrong: a third division instead of the subtract |
| `+ min = ((u16) total - sec) / 1000;` | **14, size exact** | the signed follow-up division (`mult` + `sra 31` correction) — the game recomputes `min` a second time from the 16-bit total and `sec` |
| `else if (value <= 999999)` instead of `> 999999` | **MATCH** | gcc's block layout for the last two `sprintf` paths |

The lesson is specific and reusable: when a listing shows the same quotient computed twice, once
`multu` and once `mult` with the sign correction, the source computed it twice from *different
operands* — here `(u16) total / 1000` and then `((u16) total - sec) / 1000`.

**`func_8004B1D4` (79 w) — parked at 7/79, size exact.** Whole body transcribed from the layout in one
pass: counter bump, bounds check with `printf`/`exit` at line 0x1AB, table fetch with the null check at
0x1AD, `func_8004B41C` gate, then the `flags & 3` dispatch with a linked-list walk for case 0. Restoring
the shared tail (`e->state = 2` and the counter decrement *outside* the switch, with case 0 storing and
returning early) took it from 23 to 7. The seven remaining words are the epilogue only: the game hoists
`addu $v0,$zero,$zero` above the register restores and retires the counter store after them; this build
orders the decrement before the restores. Scheduler class, issue #17. Draft in
`work/near-miss/func_8004B1D4-switch.c`.

**Conversions: 1 shipped (PR #161) from 2 attempted.** Queue 381 → 380 once #161 merges.
