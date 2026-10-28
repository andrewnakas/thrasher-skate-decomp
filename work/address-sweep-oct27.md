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
