# Address-materialisation sweep, 27 Oct (pass 20)

Goal: test the one tell the last pass proved — the direct symbolic store/load
(`lui $r,%hi(S)` + `addiu $r,$r,%lo(S)`, field offset kept as a displacement, no `$at`,
no `%lo(S+N)` fold) comes from an **incomplete-array extern** — against the whole parked
population whose residue is an address in the wrong register, a folded displacement or a
split-address mismatch.

## Results first

| body | words | result | residue after the tell |
|---|---|---|---|
| `func_8002DE18` | 18 | **MATCH** → PR #160, merged | — |
| `func_8001D804` | 23 | 10 | sum pseudo home (`addu v0,v0,v1` vs `v1,v1,v0`) |
| `func_8002FE80` | 24 | 2 | stack address in `$v0` where the game uses `$a1` |
| `func_8002DDE0` | 21 | size 0x48 vs 0x38 | loop not rotated: game has one bottom test + entry `j` |
| `func_8002050C` | 25 | 4 | `-1` sentinel CSE'd into one register + `addu` operand order |
| `func_8003B3CC` | 19 | 11 | base in `$v1` vs `$a0`; store order 0xE0/0xE4 swapped |
| `func_8003BDB8` | 31 | 6 | `0xFFFF0000` hoisted in the game, sunk by us |
| `func_8002DD88` | 22 | 3 | parameter copy lands in `$a1`; the game uses `$a2` |

9 bodies attempted, 1 converted. Every surviving residue is a register-choice or
schedule residue, not an address-spelling one — the tell removes exactly the address
difference and nothing else.

## The tell, spelled out

Fixed three words on `func_8002DE18` in one step:

```c
extern u8 D_8006F834[];              /* incomplete array: holds the symbol, not a size */
...
slot->f08 = ((Rec *) (D_8006F834 + p[3] * 0xC))->f08;   /* stride read off the sll chain */
```

produces

```
lui   $v1,%hi(D_8006F834)
addiu $v1,$v1,%lo(D_8006F834)
sll   $v0,$a0,1 ; addu $v0,$v0,$a0 ; sll $v0,$v0,2
addu  $v0,$v0,$v1
lw    $v0,0x8($v0)
```

i.e. the base materialised once, the field at its true struct offset. A *sized* extern
(`extern u8 D_8006F834[0x100]`) plus a byte-offset expression instead folds the `+8` into
the relocation (`lui $v1,%hi(D_8006F834+8)`), and a struct pointer built from a byte cast
produces `lui $at` + `addu $at,$at,$v0` + `lw %lo(...)($at)`. The stride must be taken from
the emitted `sll`/`addu` chain, not from the record the draft already had: this body's table
stride is 0xC (`(2a+a)*4`), not the 0x14 the previous draft assumed.

## The second lever (new, and what actually converted the body)

The bump-allocator body needed one instruction that four earlier shapes never produced —
`addu $a1,$v0,$zero`, a copy of the loaded pointer, with the new pointer left in the load's
own register. It appears when the **pointer variable is advanced in place and a named copy
carries the writes**:

```c
Rec *cur = (Rec *) D_8008B060;
Rec *old = cur;

cur = (Rec *) ((u8 *) cur + 0xC);
D_8008B060 = (u8 *) cur;
old->f00 = (u32) p;      /* writes go through the copy */
```

Writing `D_8008B060 = (u8 *)(slot + 1); slot->f00 = ...` instead gives the leaner one-word-
shorter body (0x44 vs 0x48) — gcc reuses the load register and emits no copy. This is the
inverse of the copy lever proved two passes ago: there the copy *killed* a pseudo, here it
*keeps* one alive so the allocator must split the load.

## Populations tested and closed in this pass

- **`-mno-split-addresses` across the whole parked corpus** (`work/scratch/flag_sweep.py`,
  187 drafts): 22 bodies improve, best improvement 3 words (`func_8002DE18` 17→14), none
  under ten words, none matching. The flag is not a converter on its own; it trades one
  address form for another.
- **`$at` population** (`work/scratch/at_scan.py`): 132 of 187 parked drafts still emit
  `$at`; the tell applies only where the listing's address is materialised once into a
  register, which the per-body diffs above cover.
- **Twin adaptation** (`func_8001D804` ← `func_800465CC`): the twin's 4-word struct copy
  transferred exactly (loads grouped, then stores), leaving only the sum's register.

## Handoff that needs a maintainer (protected path)

`func_80034B98` matches byte-exactly under `-mno-split-addresses` (verify.py measures it
`match`) but cannot ship: its body stores the literal `0x801FC000`, and `tools/scan.py`
rejects hard-coded RAM addresses. There is **no symbol** for that address anywhere in the
repo (`config/symbol_addrs.us.txt`, `config/link_aliases.us.txt`, `include/` were checked).
To unblock it, `config/symbol_addrs.us.txt` needs an entry for `0x801FC000`, e.g.
`D_801FC000 = 0x801FC000;`; the unit then reads `D_8008B0F4 = (s32) &D_801FC000;`.
That file is protected, so this is a Steward handoff, not an edit for this lane.

## Process note (cost this pass a wasted branch)

`asm/nonmatchings/game/*.s` exists for **merged** bodies too, so grepping the asm for a
symbol does not mean the body is open. `func_8002DC70` was redrafted and "matched" on the
first shape — it had been merged in `8d6d408` all along. Always check
`git ls-tree origin/main src/funcs/` first; that is what `work/enumerate.py` does through
`drafts.merged_bodies()` and why the enumerator never offered it.

## Honest projection

Of the 191 measured parked bodies, 127 are `size` and 29 `register-role`; the
near-miss list is 14 bodies within five words, and every one of the seven retested here
died on a register choice or a schedule, not on a spelling that C can still change. The
two levers that still pay are (a) the incomplete-array + true-offset spelling for address
materialisation and (b) advance-in-place-with-copy for pointer bumps. Beyond those the
lane's remaining near-misses need the original statement order, which the listings do not
carry.

## Pass 21 — the 1-to-6 word population, retested with the banked levers

Every body in the verifier's "within five words" list that is not already recorded as closed was
retested against **only** the lever its residue suggested. Merged status was checked against freshly
fetched `origin/main` (`7f30e1c`) before the first shape and the list re-checked before any PR.

| body | words | before | best after | lever tried | residue |
|---|---|---|---|---|---|
| `func_800382C0` | 12 | 1 | 1 | both `addu` operand orders, single-expression fold, separate shift local | the emitted `addu v0,$a0,$v0` operand order is not reachable: both C orders canonicalise to `addu v0,$v0,$a0` |
| `func_8002FE80` | 24 | 2 | 2 | pointer local for the stack buffer | stack address in `$v0`, game uses `$a1` |
| `func_8002BCB0` | 17 | 2 | 2 | `if (a == 0 || b == 0)` short-circuit guard | field value in `$v0`, game uses `$a1` |
| `func_80056C90` | 36 | 2 | 2 (31 with flag) | `-mno-split-addresses` | `la` temp `$v1` where the game reuses `$t0` |
| `func_80056FF4` | 39 | 2 | 3 (inline index) | remove the `slot` local | `la` temp `$v0` where the game reuses `$a0` |
| `func_8003BF7C` | 79 | 2 | 2 (74 as `u32[]` — goes gp-relative) | incomplete array vs sized array | `la` temp `$v0` where the game reuses `$a0` |
| `func_8002050C` | 25 | 4 | 4 (19 with a named sentinel) | named `-1` local | sentinel CSE'd into one register + `addu` order |
| `func_80035C14` | 34 | 4 | 4 (8 with `lo` declared first) | declaration order of the two bytes | first-created pseudo gets `$a1`, game gets `$v0` |
| `func_8002DD88` | 22 | 3 | 3 | ternary return (done last pass) | parameter copy `$a1` vs `$a2` |
| `func_8003BDB8` | 31 | 6 | 6 | constant hoist, chained stores, shifted literal | `0xFFFF0000` hoisted in the game, sunk by us |
| `func_8002DDE0` | 21 | 0x48 | 0x44 with `goto` | explicit `goto test` rotation | gcc still emits the entry test; the game's build rotated the loop |

**0 converted. Nine bodies were retested this pass** (`800382C0`, `8002BCB0`, `80056C90`,
`80056FF4`, `8003BF7C`, `8002050C`, `80035C14`, `8002DDE0`, `80034B98`); the four remaining rows are
last pass's measurements, re-checked against the current toolchain and unchanged. `80020D74` and
`80055820` were skipped on purpose: both are recorded scheduler-class on issue #17. The three `la`-temp bodies (`80056C90`, `80056FF4`, `8003BF7C`) are
the clearest result of the pass: identical residue in three unrelated functions — `lui $v0,%hi(S)` then
`lw $a0,%lo($v0)`, where the game reuses the destination register for the address
(`lui $a0,%hi(S)` / `lw $a0,%lo($a0)`). The incomplete-array spellings that fix the *fold* do not move
this register; `-mno-split-addresses` makes all three much worse (31/22/74). It is a liveness-splitting
choice in this build, not an address spelling.

`func_80034B98` is now blocked for a different reason than the record said; see
`work/handoff-80034B98.md` — the symbol the scanner wants changes the encoding, so the choice is the
maintainer's.
