## Summary

The pinned pipeline always extracts a 64-bit multiply pair **high word first** (`mfhi` then `mflo`).
The game's 64-bit pairs in this family are extracted **low word first** (`mflo` then `mfhi`). No C
source shape reaches the game's order with the pinned cc1, so the whole 16.16 fixed-point family
(func_80032C28, func_800331FC, func_8003302C, func_8003353C, func_80032E94, func_80033268) is stuck
regardless of how the body is written.

This is distinct from #76 (maspsx omitting the 3-nop latency pad) and from #17 (load-delay nop
residue): #76 fixes the number of words between `mult` and the extraction; this is the **order of
the extraction itself**.

## Evidence 1: no merged unit extracts a pair at all

I compiled every merged unit (647 files) through the pinned pipeline
(`tools/cc.py c src/funcs/<unit>.c ... --print-asm`) and scanned the emitted objects:

- merged units with a `mult`-family instruction: **12**
- `mflo` immediately followed by `mfhi`: **0**
- `mfhi` immediately followed by `mflo`: **0**

All twelve are lone uses (a 32-bit product taking only `mflo`; a lone `mfhi` from a
divide-by-constant). So there is no merged precedent in either order — the repo has never compiled a
64-bit pair, which is why none of the family has landed.

## Evidence 2: eight shapes, all high-first

One element of the multiply, compiled through the same pipeline (`work/best/order.c`):

| shape | emitted extraction |
|---|---|
| union, `u32` halves, low consumed first | `mult; mfhi; mflo; srl lo,16; sll hi,16; or` |
| union, low half into a temp first | same |
| union, signed low half | same (`sra` for the low half) |
| union, halves into temps then shifted | same |
| union, result stepped through one variable | same |
| union through a pointer | same |
| plain DImode local + shift | same + dead `sra` word |
| inline DImode shift, unsigned typedef | same + dead `sra` word |

Flag variants `-O1`, `-O3`, `-fno-strength-reduce`, `-fno-schedule-insns2`: no change to the order.

The union spelling is worth keeping anyway — it removes the frame slot and the dead `sra`, and
reproduces the game's seven-instruction tail exactly — but it cannot flip the pair.

## Evidence 3: raw cc1 vs the game (`func_80032C28`, 11 words)

Pinned cc1 output (before maspsx):

```
mult	$4,$5
mfhi	$5
mflo	$4
srl	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2
```

Game:

```
mult   $a0, $a1
nop
nop
nop
mflo   $v1
mfhi   $v0
srl    $v1, $v1, 16
sll    $v0, $v0, 16
or     $v0, $v0, $v1
jr     $ra
nop
```

Two deltas: the pair order (this issue) and the pad (#76).

## What has to change

Either of the two protected paths, maintainer's call:

1. **`toolchain/maspsx`** — maspsx already tracks `mult`/`mflo`/`mfhi` (`_handle_mflo_mfhi`).
   A post-pass that emits the low word first when both halves of a pair are consumed (and pads to
   the 3-nop gap of #76 at the same time) would close both issues together. This is the smaller,
   testable change and needs no new compiler binary.
2. **`toolchain/compiler.toml`** — if the original build used a different 2.8.x point release whose
   `mulsi3`/DImode extraction is low-first, the pin needs revisiting for this pattern. The pin was
   verified against 15 hand-written functions, none of which contains a 64-bit pair.

Nothing outside `toolchain/` can fix this; no C spelling reaches it.

## Cross-references

- #76 — missing 3-nop `mult`/`mflo` pad (same bodies, complementary delta)
- #17 — load-delay nop residue / scheduler class

Bench and listings: `work/best/order.c`, `work/best/order.s`, `work/best/exp.c`, `work/best/exp2.s`
(records branch `freebuff/records-oct26`, commit `15024d5`).
