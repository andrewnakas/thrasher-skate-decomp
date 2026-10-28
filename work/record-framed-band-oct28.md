# Pass: the never-drafted framed band, at volume (28 Oct)

Queue unchanged: fresh `origin/main` 7e24509, 663 merged, **354** unmatched.
Attempted 3 fresh bodies (all never drafted), converted **0**.

## Verdicts

| body | words | best | residue, with class |
|---|---|---|---|
| func_8001CC5C | 72 | 68/72, 0x114 vs 0x120 | **entry save order / liveness**: the game saves `$s2,$s0,$s3,$ra,$s1` and keeps a zeroed counter in `$s0` *and* a copy in `$t2` from the first block; ours saves in a different order and materialises the copies later. Prologue-first run: wrote frame 0x28 with s2/s3/ra/s1 live across the search loop and the two calls, but the `$s0`/`$t2` pair at entry is a liveness shape the frame reading does not give you. |
| func_80020078 | 77 | 76/77, 0xf0 vs 0x134 | **loop form**: the search keeps a found-flag (`$t0`) and exits on two tests (count reached, or flag set after the increment), advancing the element pointer in the branch delay slot; a `for`+`break` is 17 words shorter. Needs the do-while with the flag written as two statements. |
| func_80013D98 | 77 | 52/77, 0x128 vs 0x134 | **re-load vs named pointer**: the game re-reads `*(u32*)(s0+0x38)` before every one of the six field accesses (three `lw` chains), so the base is deliberately not held in a register; ours caches it in `p`. Also the three `func_80032C28` calls write their result straight into the gp global, which we do, but the base re-load decides the whole allocation. |

Read but not drafted: `func_80026C88` (0x80 frame, six saves, five calls — a projection body, not a
one-shape one) and `func_8001A710` (73 words, distance-squared loop with a `mult`, lands on the
`mfhi`/`mflo` side once the loop is right — #179 territory).

## Tells banked from this pass

- **The framed band's first blocker is not the frame, it is the base pointer's liveness.** In
  func_80013D98 the game reloads the record pointer before every field (`lw a0,0x38(s0)` six times);
  holding it in a local cuts six instructions and changes every register downstream. Prologue-first
  fixes the save set, but the *re-load* decision has to be read off the listing separately.
- **A two-stage search loop needs the flag, not `break`.** func_80020078's 17-word gap is exactly
  the `found` flag plus the two exit tests; `for (...; i++) { ... break; }` collapses them.

## Count and projection

3 bodies attempted, 0 converted. The never-drafted framed band is 200 bodies (93 in 80-139 words,
107 at 140+), all call-bearing; at this pass's rate (first transcription lands at 50-76 differing
words, one shape rarely closes more than a few) they are multi-pass bodies, not one-shot ones. The
one-shot population this lane ever had was the small no-call band, and it is empty.
