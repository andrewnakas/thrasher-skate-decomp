# func_8002AC14 — 86-word mixer, close-out (2026-10-28)

Branch `freebuff/records-oct26`. All measurements from `tools/match.py func_8002AC14`
against this branch; every shape was checked unmerged on freshly fetched `origin/main`.

## Decoded layout (reusable)

```
s[5]            record count
s + 0x10        array of 4-byte record pointers
rec[0]          table index  (base = *(u8**)(D_800A4F00 + 4) + rec[0]*0x9C)
rec[1]          entry count  (inner loop trip count)
rec[4]          sub-table pointer
*(base + 0x48)  output pointer;  out = obj + tbl[4]*0xC
tbl[0..2]       per-channel bias (+ tbl[5]<<9 for the scale, tbl[4] for out index)
channel         ((ch - 0x80) * (tbl[5] << 9)) >> 16, + bias, clamped to 0..0xFF
stores          out[8], out[9], out[0xA];  tbl += 8 per entry
```

`0x9C = 0x4F00*(... )` is the listing's `sll 2 / addu / sll 3 / subu` chain:
`(rec[0]*4 + rec[0])*8 - rec[0] = rec[0]*39*4`.

## Shapes measured

| # | shape | size | matcher |
|---|---|---|---|
| v1 | `p = s+0x10+i*4`, `rec = *p`, walk −4 | 0x158 (86) | 74/86 |
| v2 | `p = (u8*)(s + i*4)`, `rec = *(u8**)(p+0x10)`, walk −4 | 0x154 (85) | 81/86 |
| v3 | index form `((u8**)s)[i+4]` | 0x154 (85) | 81/86 |
| v4 | v2 + `scale2 = scale` (forced duplicate scale) | 0x154 (85) | 81/86 |
| v5 | v2 + `-fno-strength-reduce` | 0x14c (83) | 83/86 |

v2/v3 are the shapes that reproduce the listing's *fold* (`sll; addu; lw 0x10(base)`) and its
pointer walk (`addiu base,base,-4`). Their 81-diff matcher number is worse than v1's 74 only
because the matcher aligns by index and v2 shifts three words later. The structural comparison
below is the one that matters.

## The residue, isolated

Shift-aware alignment (difflib over register-normalised, branch-target-normalised listings)
leaves exactly two difference blocks and no others:

```
ours  preheader : andi v0,a1,0xFF ; addiu t7,v0,-0x80     <- three of these, hoisted
game  loop      : addiu a1,t7,-0x80 ; mult a1,a2          <- same op, per use, in-loop
game  loop only : addu t2,a2,zero   (first clamp's bnez delay slot)
```

So: ours is 3 words longer in the preheader, the game is 4 words longer in the inner loop,
size 85 vs 86. Nothing else differs.

Both halves are one compiler decision: loop-invariant motion. `cr - 0x80` is invariant, and
gcc 2.8.1's `move_movables` hoists it here; the game's build kept the masked channel in `t7`
and re-did the `addiu` at each use. The game's extra live value in the inner loop (`t2`, a
duplicate of the scale register `a2`) is the plausible reason its invariant motion refused —
one more live value at the point where the hoist would land.

Forcing that duplicate from C fails for a measured reason: the two pseudos hold equal values,
so copy propagation rewrites all uses to one pseudo and the allocator coalesces them.
`scale2 = scale;` (v4) left the object byte-identical to v2. `-fno-strength-reduce` (v5) does
not disable `move_movables` and only degrades the body.

**Class: invariant motion + equal-value register duplication — compiler-bound.**
Proof is the emitted listing above, not an assertion; the two blocks are the entire residue.

Best draft: `work/best/func_8002AC14-s5.c`.

## Queue

No unit merged this pass. Config-based counts in the game range (`< 0x80058634`):
**647 merged, 435 unmatched** of 1082 game functions (`config/functions.us.csv`). The lane's
filtered C-work number (handwritten / coprocessor / $at-as-base bodies removed) was not
re-derived this pass, so compare it to the previous record rather than to 435.

Pipeline green on this branch: `scan.py` 0 problems / 647 files, `gate.py` GATE PASS,
`build.py` BUILD PASS, `SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.

## Conversion this pass: func_8002C284 (71 words, 0x11C)

PR #180, branch `freebuff/8002C284`, from `origin/main` (`7e24509`).
Measured 23 → 16 → **MATCH** in three shapes on top of the old near-miss (which was 20 at a
wrong control-flow shape).

The shape that closed it — two source facts, both read off the listing:

1. the range test is on the **shifted** value, two-sided:
   `v = (tbl[n->idx] + n->off) << 16; if (v < -0x100) … else if (v >= 0x101) … else …`
   This is what puts the second `slti` in the first branch's delay slot (game 0x2E0). Writing
   the test as `(s16)…` instead makes gcc sign-extend (`sra`) and use `bgez`/`blez` (16 diffs).
2. every arm is a **positive** test with the emit as the `else`:
   `if (n->a) func(n->a); else *D_8008B048++ = n->val;`
   The inverted form (`if (!n->a) { emit; return; } call;`) is only equivalent for the first
   two arms; for the middle arm's second test it lays the emit before the call and the whole
   tail shifts by 8 words.

Verified on the PR branch from `origin/main`: `scan.py` 0 problems / 664 files, `gate.py`
GATE PASS (664/664), `build.py` BUILD PASS,
`SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.

Queue after this pass: 1082 game functions, **665 merged once #180 lands, 417 unmatched**.
Raw config count on `origin/main` today: 664 merged / 418 unmatched.
