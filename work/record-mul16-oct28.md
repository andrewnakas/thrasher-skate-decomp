# Pass: the 16.16 multiply's 64-bit temporary (28 Oct)

## The experiment: which spelling keeps the halves in registers

Test bench: one element of the 16.16 multiply through `tools/cc.py ... --print-asm`, i.e. the real
pipeline (`cpp | cc1 | maspsx`), pinned flags. Five spellings:

| # | spelling of the 64-bit intermediate | emitted tail | verdict |
|---|---|---|---|
| 1 | `s64x p; p = v[0]; p = p * k; v[0] = (s32)(p >> 16);` | **full 64x64 multiply** (`multu`+`mult`+`mflo`+`mfhi`, 4 products) then `srl/sll/or` + dead `sra` | worst: widens both operands |
| 2 | inline `v[0] = (s32)(((s64x)v[0] * k) >> 16);` | `mult; mfhi; mflo; srl lo,16; sll hi,16; or` + **dead `sra hi,16`** | right count, dead word |
| 3 | `u64x` typedef, both operands cast | same as 2 with `srl` dead word | same |
| 4 | halves read through `s64x *pp = &p` | same as 2 (pointer folded away) | same |
| 5 | **`union { long long w; struct { u32 lo, hi; } h; }`**, halves consumed as `u32` | `mult; mfhi; mflo; srl lo,16; sll hi,16; or` — **no stack home, no dead word** | **the answer** |

So the union view is what removes the stack home: it makes the two halves two SImode values, so
gcc never forms a DImode shift and never needs the 64-bit temp in memory. `long long` is the only
spelling available (`s64` is not in `include/common.h`, a protected path), and `long long` alone
(the DImode shift) always spills when several products are live.

Proof files: `work/best/exp.c`, `work/best/exp2.c`, `work/best/exp.s`, `work/best/exp2.s`.

## What the union spelling bought, and what is left

With the union spelling:

- func_800331FC: 35/27 -> **28/27, size 0x70 vs 0x6c (one word over)**. Per-element sequence is now
  the game's, instruction for instruction: `mult; mfhi; mflo; srl lo,16; sll hi,16; or; sw`.
- func_8003302C: 34/29 -> 31/29, size 0x7c vs 0x74.
- func_80032C28 (the primitive itself, 11 words): instruction set exact, 2 words short/over set aside.

The residual in all three is the same **pair order**: the game has `mflo` before `mfhi`;
our cc1 emits `mfhi` before `mflo` for every one of the five spellings (raw cc1 output checked
before maspsx, so this is cc1, not maspsx). It is not a toolchain impossibility: the corpus has
both orders in non-handwritten listings (func_80032C28 `mflo` first; func_8003C290 `mfhi` first),
so the order follows the expression shape and the family needs one more source form that
consumes the low word before the high one.

`-fno-schedule-insns2` on the pair changes nothing; `-fno-schedule-insns` is rejected by cc1.

## Other bodies this pass (no conversions)

| body | best | residue |
|---|---|---|
| func_8002AB64 | 47/44 | dead stores of both `mult` operands into two 8-byte slots; both success paths funnel to `return rec` |
| func_8002C148 | 22/27 | CFG: game branches to one shared `return 0` and materialises `1` in `$v0`; ours inverts with `xori` and has two `jr ra` |
| func_8001D540 | 27/28 | loop rotation: skip-first path computes the cursor in the `bnez` delay slot and re-enters the head test |
| func_8004F1E0 | 23/28, **0x6c vs 0x70 (one short)** | nested-ifs + single trailing return fixed the two-return problem; the missing word is the game's `addu v0,a0,zero` copy of the table index, which our allocator coalesces away |
| func_8002DA40 | 31/33, 0x80 vs 0x84 (one short) | three midpoint/deviation groups; game places `sh mid` and the next `lh` before the `bgez`, ours uses the branch delay slot — scheduler class |

## Queue

Fresh origin/main unchanged this pass: 663 merged units, clean enumerator **354** unmatched.
Attempted 5, converted 0. Best drafts in `work/best/` (`func_8004F1E0-s3.c`, `func_8002DA40-s2.c`,
`func_800331FC-s1.c`, `func_80032C28` variant lost to the spelling change — see `work/best/exp*.c`).
