# pass oct28s — shapes on the four parks from oct28r

## func_8001A550 — 33/106 → **25/106, size exact**, then parked

Two of the three ordered levers paid, both on the argument reading and the "don't name a re-loaded
base read" rule:

| # | change | measurement |
|---|---|---|
| 0 | kept draft | 33/106 |
| 1 | name the key (`key = a0->unk0;` before the scan) so gcc stops re-loading `0x0(s1)` per iteration | **25/106** |
| 2 | drop the cached `a0->unk8` local and read it inline at each of the four uses | same 25/106 (both changes measured together) |
| 3 | struct entry type + `for (i = 0, p = base; i < n; i++, p++)` | 107/106, 1 word long — reverted |
| 4 | `for (;;) { if (match) break; if (++i >= n) break; p++; }` | 107/106, 1 word long — reverted |

Shape 3 and 4 both added a redundant top-of-loop test that the game does not have. The game's loop
enters with the key compare, increments `i`, tests `i < n`, and puts `p += 0x18` in the branch delay
slot. The do-while form reproduces the tail exactly but gcc rotates it: it pre-loads the first element
(`lw $v0, 0($v0)` before the loop) and uses the entry register as the zero for `i`. That rotation is the
whole remaining residue — 25 words, size exact, no missing instruction.

Residue class for the next attempt: **loop rotation**, turn-on being whichever spelling makes gcc emit
the compare-first body without a hoisted first load. Three loop spellings are now eliminated with
measurements.

## Second shapes on the other three parks

| body | before | second shape | after |
|---|---|---|---|
| func_8001D9C8 | 98/107, 1 short | pointer `for`-loop for the flag-and-goto scan | **91/107, 1 word long** |
| func_8001CAA8 | 108/109, 4 short | do-while outer + `while` inner instead of gotos | **93/109, size exact** |
| func_800282E4 | 112/109, 4 long | byte pointer advanced by 0x160 instead of typed `e += 1` | 112/109, unchanged |

The 1CAA8 change is the big one: converting the goto loops to ordinary loops moved it from 4 words short
to size exact and nearly doubled the matching words. Its residue is now allocation inside the two walks,
not structure.

The 282E4 pointer change made no difference at all, so the 4 extra words are not the 0x160 scaling —
that conclusion is now measured rather than assumed.

## State

Conversions 0, bodies re-shaped 4, PRs 0 (nothing matched). Best drafts are in `work/best/`.

Pipeline: scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`. Worktree 684 = 684.
