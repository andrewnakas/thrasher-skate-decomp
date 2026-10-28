# pass oct28q — fresh-body transcription, whole-body first measurement

Instruction: leave the two size-exact parks alone, take 5+ untouched fresh bodies, write each whole
from its listing, measure once, park if more than a few words out.

## Result: 1 body attempted, 0 converted

| body | words | first measurement | outcome |
|---|---|---|---|
| func_8001FD54 | 105 | **39/105, size 0x19c vs want 0x1a4** | parked — 2 words short of frame/body |

The pass ran out of budget on the first body: the decode was written whole from the listing
(prologue 0x38, save set s0/s1/ra, three 0x18-stride fields, the squared-distance cull, the
one-argument sign-fix second cull, the reversed store order), and it came back 2 words short with
38 matching words out of 105 — the closest first measurement this lane has had on a fresh body.

## The one experiment run, and its measured direction

The 2-word gap sits around a stack block: the game spills the three distance temporaries to
`sp+0x10`, `sp+0x14`, `sp+0x18` and keeps its loop counter at `sp+0x20`, which is what makes its
frame 0x38 rather than 0x28. Reading that as the banked "widen the declared extent of the stack
block" lever, the draft was rewritten to use a `s32 w[6]` block with the counter in `w[4]` and the
out-parameter at `&w[4]`, so gcc would be forced to address the block the way the game does.

It regressed: **39/105 @ 0x19c → 84/105 @ 0x1b0** (4 words too long). Reverted verbatim; the
kept draft is `work/draft-8001FD54.c` at the 39/105 form.

What that measures: array-index addressing through `w[]` costs extra address arithmetic per use
(`sll`/`addu` per element) that the game does not spend, so the game's three spills are not
element stores through an indexed block — they are scalar locals that gcc happened to keep on the
stack. The widen-the-block lever applies to a block a *callee* writes into (a stack argument or an
out-parameter), not to temporaries the body itself re-reads, where the indexed form adds words.

Next residue on this body, named: the two missing words are the two scalar spills of the squared
distances that the game keeps in its frame, with the turn-on being whichever source shape makes
gcc 2.8.1 spill those two intermediates while the register draft keeps them live.

## State

Conversions 0, bodies attempted 1, parks 1 (39/105, size 2 words short). No PR: nothing matched.

Pipeline on a clean tree: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`.
Worktree 684 local = 684 upstream.

Queue: **398 open in range, 227 attempted, 684 merged.**
