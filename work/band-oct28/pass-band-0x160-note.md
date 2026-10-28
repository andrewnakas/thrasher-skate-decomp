# Pass: band 0x160-0x1B8 (88-110 words, call-bearing) — whole-body transcription

Method this pass: read the frame and the exact save set/order off the listing first, then write the
whole body in one pass in the listing's statement order, measure once, correct only what measurably
differs. Permuter only on bodies already instruction-complete at 1-2 words.

## Verdicts

- **func_8004DA90** (88 words, 5 calls) — **2 of 88**. Structure landed on the second shape, and both
  rules are worth keeping:
  * the distance test is `if (d < limit) { ...; return 0; } ...; return 1;` — fail block last, reached
    by `beqz`. Writing it as `if (d >= limit) { return 1; }` first makes gcc invert the branch and
    branch *over* the then-block, shifting the whole tail.
  * the two zero tests are a positive `&&` chain (`if (w0 != 0 && w2 != 0) { A } else { B }`), not
    `if (w0 == 0 || w2 == 0) { B } else { A }`: the `||` form puts B first and inverts the second test.
  Residue: the second compare value's home — game `lw $a1, 0x18($sp)`, ours `lw $v0`. Allocation.
  Permuter: 2486 iterations, base score 10, min score 10, never improved. Park.

- **func_8001EB4C** (89 words, 4 calls) — **32 of 89**, size 0x168 vs 0x164 (+1 word).
  Everything but one join matches: the first call argument (`f & 0x7FFF` OR-ed with the four flag bits)
  lands in `$a2` where the game has `$a0`, and the two `addu $a0,$a2,$zero` copies that costs are the
  entire size gap. Root cause is the loop's byte-offset variable taking `$a0`; moving that declaration
  after `arg0`'s does not move it. Named table base (`extern u8 D_8006F2C0[]; u8 *base = D_8006F2C0;`)
  is what produces the game's `lui/addiu` pair into its own register instead of folding `+2` into the
  hi/lo. Park (allocation).

- **func_8002D198** (102 words, 1 call) — **42 of 102**, size 0x190 vs 0x198 (-2 words).
  Head matches exactly, including the branch: `if ((r1 ^ r2) >= 0) return 0;` is the right source form
  for the game's `xor` + `bgez` sign test (do not write it as two sign compares). Tail: our gcc merges
  and hoists the three `out[]` evaluations, the game finishes each before starting the next, which is
  the two lost nops; `t` lands in `$a0` here and `$a1` in the game. Park (scheduler + allocation).

- **func_80017740** (95 words, 12 calls) — instruction-complete at entry, 16 words differing by
  register name only. Permuter: ~3100 iterations, base score 95, min score 95. Park (allocation).

## Permuter, measured again

Its score is monotone in the differing-word count (10 at 2 words, 95 at 16), and in four passes it has
never moved a base score. Keep the threshold: only hand it bodies that are instruction-complete *and*
at 1-2 words, with a short budget, and expect nothing.

## Queue

670 merged units on `origin/main`; 412 unmatched listings still open.
