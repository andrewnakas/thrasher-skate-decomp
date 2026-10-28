# Prologue-first pass, 28 Oct 2026

Method under test: read the frame size and the exact save set/order off the listing *before* writing any
body, decide from that which values must stay live across calls, then write the whole body to that frame.
Four never-drafted bodies, each measured once per shape, cap three shapes.

## What prologue-first actually settles

| body | frame | save set / slot order (game) | first transcription | after 3 shapes |
|---|---|---|---|---|
| func_8002C284 | 0x20 | s1@0x14 s0@0x10 ra@0x18 | frame size + all slots exact, 6/6 prologue words match | 0x20 exact, 31 words differ (block layout) |
| func_8001CC5C | 0x28 | s2@0x18 s0@0x10 s3@0x1C ra@0x20 s1@0x14 | frame + slots exact, 5/6 prologue words | size 0x124 vs 0x120, 65/72 (save *order* s0/s3 + 1 word) |
| func_800190E0 | 0x30 | s5@0x24 ra@0x28 s4@0x20 s3@0x1C s2@0x18 s1@0x14 s0@0x10 | **whole prologue word-exact** (7 saves + frame) | 3 words long, 69/76 (gp-base form) |
| func_80013D98 | 0x18 | s0@0x10 ra@0x14 | **whole prologue word-exact** | 0x104 vs 0x134, 64/77 (missing field reloads) |

So: **the frame and the save set are no longer discovered after the fact — 4 of 4 bodies got the frame size
and the complete slot map right on the first transcription, and two of four got the prologue word-exact.**
That half of the allocation class is now a solved, mechanical step.

## What it does not settle

The residue moves out of the frame and into the body, and it is a different class each time:

- func_8002C284 — the same multiset of blocks in a different emission order (three inline `jal`+`j` paths vs
  the game's shared recurse block). Two shared-block spellings tried; the shared form loses 5 words to gcc's
  cross-jumping. Class: **block layout**.
- func_8001CC5C — save *order* inside the prologue (game saves s0 between s2 and s3; ours emits s3 first) plus
  one extra word from the `return 0` block not landing in a jump delay slot. Class: **save order / layout**.
- func_800190E0 — the gp-relative table base: game emits `addiu $x, $gp, %gp_rel(sym)` then `lw 0x18($x)`,
  ours folds the +0x18 into the address (`lui`/`addiu`). Materialising the base in its own statement made it
  worse (69 -> 73), so the fold is not broken by the known lever here. Class: **gp-base materialisation**.
- func_80013D98 — the game re-loads `obj->f38` three times where gcc CSEs it into a register. Inlining the
  field expression and marking the field `volatile` both left the object size at 0x104 vs 0x134, so this
  particular reload is not reachable from source in this toolchain. Class: **forced reload (CSE)**.
- func_80020078 (5th body, 1 call, frame 0x28) — size exact first try, 63/77 differ, but gcc hands the saved
  registers out in a different order again (s1=i, s2=d against the game's s1=d, s2=p6). Class: **register role**.

## Verdict

Prologue-first is a real improvement in *where the pass spends its shapes*: the frame question is answered
before the first compile instead of after the third, and no body in this batch was ever short or long for a
missing save. It does **not** convert bodies by itself — 0 of 5 — because the wall behind the frame is not
one class but four (block layout, save order, gp-base form, forced reload), and each needs its own lever.
The honest projection: prologue-first should be the default opening for every framed body, but its payoff is
one shape saved per body, not a conversion rate.
