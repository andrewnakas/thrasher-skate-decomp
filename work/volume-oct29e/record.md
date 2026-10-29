# Pass oct29e — two ordering defects fixed, two residues named

Tree `7605c52` = `origin/main`; no branch switched, no unit file overwritten.

## `func_80034874` — the regression reverted, `p` born early: 41 → 64 matching

Two changes only:
1. **Reverted** the previous pass's regression: `r = c.f4 - 8` sits **before** `func_8005A0A8(&b)`, which
   is what puts its `addiu` in that call's delay slot as `$s7`.
2. Moved `p = D_800A5634` above `func_8005A234(&c)`, so the pointer is genuinely live across that call
   and takes a callee-saved register from entry.

Result **129/129 words, 64 matching** (was 41). Frame 0xC0, every record offset correct.

Surviving residue, from the alignment:
- the prologue's constant/save interleave — the game opens `lui $a1,0xE100` / `ori` first, then
  `addiu $a0,$sp,0x28`, then `$s2 = 0x10`, `$s6 = 0`; ours emits `$s2`/`$s6` first and the constant after
  (`0x800348B0`);
- the `v == 0x20 || v == 0` test compiles to `bnez` + a `j` where the game has two forward `beqz` to the
  same block, and the game's `addiu $s4,$s4,1` sits in the first `beq` delay slot (`0x8003494C`).

## `func_8003599C` — both bytes named up front: frame closed

Naming `b1 = p1[0]`, `b2 = p2[0]`, `n1 = p1[1] >> 4`, `n2 = p2[1] >> 4` before the first dispatch closed
the frame to the game's **0x20** and lifted matching from 2 words to **61**. Size **132/137**.

The 5 missing words are one gcc cross-jump, and the alignment says so exactly: the *second* dispatch's
`default` block is gone. Both defaults compile to the identical five words
(`sll $v0,$a1,1; addu $v0,$v0,$a1; sll $v0,$v0,4; addu $v0,$v0,$v1; sw $zero,4($v0)`), so gcc emitted
one copy and branched both switches to it; the game keeps two. No CFLAGS in the allowed list disables
cross-jumping, so this is not a shape the source can express.
Turn-on: `0x80035B90`.

## Count

conversions **0**, bodies measured **2** (`func_80034874` 129/129 at 64 matching, `func_8003599C`
132/137 at 61 matching). No PR. Queue at `7605c52b`: 74 open (fresh), 238 attempted, 693 merged units.

Both bodies improved by the mechanism the record predicted; neither crossed. The walker's remaining gap
is scheduling order in the prologue, which is the class this lane has never been able to steer.
