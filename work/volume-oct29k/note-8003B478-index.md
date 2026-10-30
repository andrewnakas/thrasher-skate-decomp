# func_8003B478 — the index rebuild is worse; body retired under class F

One measurement, same draft and same declarations as `work/volume-oct29j/note-8003B478.md`:

**Pointer walk (best, kept): 39 of 71 words match, size 0x11c vs 0x11c (exact).**
**Explicit `s32` index rebuild: 6 of 71 words match, size 0x110 vs 0x11c (three words short).**

It moved the wrong way — the index form lost 33 matching words and three instructions. The reason is
visible in the alignment at `0x8003B48C`: the rebuild homed the three invariants in `$t0`/`$t1`/`$a3`
and then emitted `addu $a2,$zero,$zero` for the counter, so the game's `slti $a3` / `addiu $a2,0x1` /
`addiu $a1,0x100` ordering is still not produced, and the index form additionally pays the array
scaling instead of the game's `addiu $a0,$a0,0x70` walk.

Retired in `closed-by-evidence.md` as **class F** (induction-pointer bias under a signed loop test) with
turn-on `0x8003B48C`, the list of seven spent shapes, and the merged evidence: 21 merged units emit
positive-displacement pointer walks, but every one tests equality, not a signed `slt`. The best draft
stays at `work/best/func_8003B478.c`; the rebuild is kept beside it as `work/best/func_8003B478-index.c`.
