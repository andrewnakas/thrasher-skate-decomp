# Pass: hunting the mflo-first shape (28 Oct)

## 1. The merged-unit search: it has no answer, and that is proved

The pass asked for merged units whose compiled objects emit the low word first. There are none.
I compiled **all 647 merged units** through the pinned pipeline
(`tools/cc.py c src/funcs/*.c --print-asm`, parallel, outputs kept in /tmp/mflo) and scanned every
emitted object for `mflo`/`mfhi`:

- merged units containing a `mult`-family op: **12**
- merged units emitting `mflo` immediately followed by `mfhi`: **0**
- merged units emitting `mfhi` immediately followed by `mflo`: **0**

The 12 are lone uses: a 32-bit product taking only `mflo` (e.g. `x * x` in func_8004D0E0) or a lone
`mfhi` from a divide-by-constant (`y * D_8008A934 / 1000`). No merged unit anywhere in the repo does
a 64-bit pair extraction. So there is no in-repo precedent to copy, and the whole 64-bit pair family
is outside merged work — which is why six of its bodies are still open.

## 2. The bench: eight shapes, both orders, one conclusion

`work/best/order.c`, one element of the 16.16 multiply each, compiled with the real pipeline:

| shape | tail |
|---|---|
| union, u32 halves, low consumed first | `mult; mfhi; mflo; srl lo,16; sll hi,16; or` |
| union, low into a temp first | same |
| union, signed low half | same, `sra` for the low half |
| union, halves into temps then shifted | same |
| union, result stepped through one variable | same |
| union through a pointer | same |
| plain DImode local + shift | `mult; mfhi; mflo; ...; sra` (dead word) |
| inline DImode shift, unsigned typedef | `mult; mfhi; mflo; ...; sra` (dead word) |

Every shape emits **`mfhi` before `mflo`**. Flag variants (`-O1`, `-O3`, `-fno-strength-reduce`,
`-fno-schedule-insns2`) do not change the order either. The union spelling is still the one that
removes the stack home and the dead `sra`, so it stays banked.

Conclusion: with this cc1, the DImode pair is always extracted high-word first. The game's 27
`mflo`-first pairs (including non-handwritten func_80032C28) therefore cannot come from any source
shape tried here. This is a **compiler-bound class pending a toolchain question**, not a drafting
problem: the pin was made on 15 hand-written functions, none of which uses a DImode pair.
Evidence for a maintainer: `work/best/order.c`, `work/best/order.s`, `work/best/exp*.s`, and the
raw pre-maspsx cc1 listing for func_80032C28 (below).

```
mult	$4,$5
mfhi	$5
mflo	$4
srl	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2
```
(the game wants `mult; nop;nop;nop; mflo; mfhi; srl; sll; or; jr; nop`)

## 3. One new lever, and the closest body

**Offset-left address with a truncated base.** On func_8004F1E0, `base + idx * 0x4C` leaves the body
one word short (0x6c vs 0x70); writing `(s32) idx * 0x4C + (u16) D_800AFCA4` restores the game's
extra word and takes the body from 23 differing words to **14, size exact**. The `(u16)` cast on the
base is what stops gcc folding the offset into the symbol and keeps the separate `addu`.

After that: two permuter runs (928 and 902 compiles, ~400 s) plateau at 13 words differing with the
size exact — allocation residue. Parked as such; best draft `work/best/func_8004F1E0-s4.c`.

## 4. Queue and count

Fresh `origin/main` 7e24509: **663** merged units, clean enumerator **354** unmatched.
Attempted this pass: the merged-unit sweep, the 8-shape bench (4 flag variants), func_80032C28,
func_800331FC, func_8003302C, func_8004F1E0 (with permuter). Converted: **0**.
