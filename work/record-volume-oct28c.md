# Six-body drafting pass, 2026-10-28 (c)

Branch `freebuff/records-oct26`. Every candidate was checked unmerged against freshly fetched
`origin/main` (`ebba874e`) before a shape was written, through `lane/select.py`'s guard.

**Attempts: 6. Conversions: 0. Queue unchanged: 676 merged / 406 open.**

## The selection defect worth recording

`work/` is gitignored, so the working tree cannot see a parked draft that lives only on this
records branch. `work/record-8002AC14-oct28.md` already existed when this pass re-drafted
`func_8002AC14` as "never drafted" — it has been closed out at 81/86 since an earlier pass.
**Unmerged against `main` is not the same as never attempted.** The candidate enumerator must read
attempt state from this branch (`git ls-tree freebuff/records-oct26 work/`), not from the working
tree. Until it does, a "never drafted" list built in a main-based tree overstates fresh ground by
roughly the number of parks on this branch.

## Per-body table

| function | words | best | residue class | the instruction it turns on |
|---|---|---|---|---|
| func_80032FF4 | 13 | **12/13** | allocation — identical instruction multiset, register homes only | `lw $t0, 0x0($a0)`: game loads the six words into `$t0-$t5`, ours into `$v0,$v1,$a1-$a3,$t0` |
| func_80033818 | 13 | **12/13** | allocation — order identical, registers only | `lw $t0, 0x4($a0)`: same six-to-`$t0-$t5` home |
| func_80032400 | 27 | **6/27** | copy propagation + prologue copy order | `addu $s0, $a2, $zero` (0x80032408): game copies `$a2` first, ours copies `$a1`; and the else arm stores `$a1` where ours stores `$s1` |
| func_8002BCF4 | 28 | 12/28 | preheader/scheduler placement | `addiu $s0, $v1, 0xC` (0x8002BD20): game delays it past the entry test, ours hoists it above |
| func_8002AC14 | 86 | 77/86 | re-test; previous close-out 81/86 — scheduler placement of the loop-invariant symbol | `addiu $t8, $v0, %lo(D_800A4F00)` (0x8002AC28): the game materialises the base right after the `bltz`, ours after the RGB extraction |
| func_8005737C | 109 | 68/109 | block/arm placement in a three-case switch | `addiu $v0, $zero, 0xC00` (0x80057438): game lays arm 0 immediately after the dispatch and both the `beqz` and the fall-through land on it; ours lays arm 2 there and adds a `j` |

Drafts: `work/pass-oct28/`. None of the six is a spelling question — the two 13-word bodies have the
game's exact instruction sequence and differ only in which temporary holds each value, which is the
class filed in #191.

## What the banked rules did and did not buy

- **Prologue-first** decided the frame and save set correctly on all three framed bodies
  (`0x20`/`$ra,$s0,$s1`, `0x20`/`$ra,$s0,$s1`, `0x20`/`$ra,$s0,$s1,$s2`) — every frame and save set
  came out right on the first transcription. It does not decide the *copy order* inside the prologue
  (`func_80032400`).
- **`sltiu` wants a `u32` counter** — `func_8005737C` went from `slti` to the game's `sltiu` by
  changing the loop counter from `s32` to `u32`. Confirmed again.
- **`-G8` on a small extern** — `extern u8 D_800A4F00[8]` produced `lw $v1, 0x4($gp)` where the game
  uses `lui/addiu` + `lw 0x4($t8)`. Widening the declaration to `[0x100]` restored the absolute form.
  That is the banked rule in `func_8004912C` shape, hit again from the other direction.
- **`-mno-split-addresses`** applied under the measured rule (no call, symbol high word in the
  `bltz` delay slot) and moved `func_8002AC14` 81→77 on this shape.
- **One statement per operation** converted `func_80032400` from 12/27 to 6/27 by naming the
  multiply's operands and its result separately.

## Blocked, unchanged

`func_80034B98` still **MATCH**es and still cannot ship: `D_8008B0F4 = 0x801FC000` trips
`scan.py`'s hard-coded-address rule, and no symbol exists at 0x801FC000 (the highest rodata symbol is
`0x80011B2C`, and `config/symbol_addrs.us.txt` is empty). That is issue #101, one line in a protected
path; re-verified this pass.
