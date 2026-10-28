# Fresh band, five bodies: two conversions, 2026-10-28 (e)

Branch `freebuff/records-oct26`. Candidates came from `lane/select.py list --fresh --min 70`, i.e. never
drafted anywhere in this branch's records, ascending size.

**Conversions: 2 — func_80026C88 (PR #197) and func_8002673C (PR #198). Attempts: 5.**
Queue: 676 merged + 2 in review, 404 open.

## Per-body table

| function | words | best | outcome / residue |
|---|---|---|---|
| func_80026C88 | 73 | **MATCH** | shipped, PR #197 |
| func_8002673C | 77 | **MATCH** | shipped, PR #198 |
| func_8001974C | 78 | 32/78 (0x120, want 0x138) | parked — prologue copy order (`sw $s4` before `sw $s3`: the game homes the second parameter's register first and masks `$a0` itself) plus six words missing in the tail |
| func_80034F14 | 83 | 67/83 (0x134, want 0x14C) | parked — six words short after the frame and both loop preheaders lined up; the `memset` call and the bank/slot split are the remaining structural gap |
| func_8002FFDC | 84 | 64/84 (0x144, want 0x150) | parked — the game stores `u16` to `+8` and then **re-loads** it as `lh`; gcc forwards our store into a register (`sll $s2,$v1,16`) instead of emitting `sh` + `lh` |

## What closed the two

Both were the same lever, and it is now four confirmations old:

**offset-left address form** — `(u8 *) (a1 * 140) + (u32) a0 + 0x48` rather than `a0 + a1 * 140 + 0x48`.
The first spelling is `addu $a0, $a0, $s4` (offset + base) and the second is `addu $a0, $s4, $a0`
(base + offset); that single operand order was the whole of func_80026C88's 2-word residue, and in
func_8002673C it also moved the second argument out of `$v0` and back into `$a1`.

Second lever, new and worth banking: **the stack block's declared extent decides the frame.**
`func_80026C88` and `func_8002673C` both needed `u32 t[12]` for a structure the callee only writes eight
words of. With `t[8]` the frames were 0x70 instead of 0x80 and 0x60 instead of 0x70, and every stack
argument was at the wrong offset; widening to twelve words fixed frame, argument loads and save area in
one step (20/73 → 2/73 and 25/77 → 8/77 before the address form, then both MATCH).

Third: **do not name a base that the listing keeps re-materialising.** `func_80034F14` carried
`u8 *banks = D_800A6244;` in a register and needed an extra saved register for it; indexing the symbol
directly dropped the frame from 0x28 to the game's 0x20 and took it 82/83 → 67/83.

## Rule check

- Prologue-first again got every frame and save set right on the first transcription (0x80/`$s0-$s5`+`$ra`,
  0x70/`$s0-$s5`+`$ra`, 0x28, 0x20, 0x28).
- `signed vs unsigned` (last pass's note) did not come up in these five; the `sltu` in
  `func_8002FFDC`'s distance is `func_80032D3C`'s, not this body's.
- The permuter was not used: no body reached one differing word.
