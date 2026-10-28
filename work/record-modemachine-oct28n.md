# The mode machine, drafted whole; two more of the narrowed list, 2026-10-28 (xii)

Conversions 0, bodies attempted 3, parks 3. All three were written whole from their listings in
one pass each and measured at the end; none was shaped in pieces. Pipeline green on a synced tree.

## func_80052874 (231) — the corrected decode, drafted as an if-chain

The previous record's turn-on instruction was wrong in two ways and both are now settled from the
listing, not from memory:

- **There is no jump table.** The only `jr` in the whole listing is `jr $ra` at 0x80052C08. The
  dispatch on `D_8008A9FC` is `beqz` at 0x800528A4, then `bne $v1, 1` at 0x800528B0, then `bgtz` on
  `D_8008A9F0` at 0x800528C0. It is an `if/else if` chain in that arm order.
- **The init arm does not store zero into `D_800B134E`.** The `sb` in the `memset` delay slot is
  `sb $v1, %lo(D_800B134E)`, and `$v1` holds `D_8008A9FC`, which is 1 in that arm. It stores the
  mode value, and the store is written *before* the `memset` call (the compiler sinks it into the
  call's delay slot, which is why it executes first).

It is also not a mode machine in the abstract: it is the SPU voice-attr tick. `p->unk30` slides by
`p->unk38` inside `[.., unk34]` and clears the movement flag (bit 0 of `unk2C`), the attr block is
`{s32 mask; s32 3; s16 unk8; s16 unkA}` inside the full **0x40-byte** `SpuVoiceAttr` (that size is
what makes the frame 0x70 with a second 8-byte scratch at 0x50), and the tail is a ring-buffer feed
with `EnterCriticalSection`/`ExitCriticalSection` around the position update.

| shape | result | notes |
|---|---|---|
| whole body, attr as 0x10 bytes | 203/231 @0x33c | frame 0x48, 24 words short |
| attr widened to 0x40, scratch 8 bytes | 195/231 @0x34c | **frame exact 0x70**, head matches to 0x80052900 |
| movement clamp written as one shared test (`step > 0 ? high : low`) | 195/231 | loop now compares in the game's order |
| flag word spelled through the symbol (`D_800B134C.flags`) so its base can split from the pointer | **194/231 @0x358** | +3 words recovered; both bases now appear |

**Park, 194/231 @0x358 (want 0x39c).** Two named residues:

1. *17 words short in the transfer tail.* The game re-materialises `D_800B1364` and re-reads
   `p->unk18` in each of the three `func_80053774` continuations; my `goto clear` shares the store
   and the reload. Turn-on instruction: `lw $a0, 0x18($s2)` at 0x80052B78 — the first feed's
   short-write arm computes its second argument from the *pointer* after the flag store, not from
   the local the branch already produced.
2. *The clamp block is emitted in-line after the loop; the game hoists it to 0x8005290C, before the
   mode-dispatch tail.* Turn-on instruction: `beqz $v0, .L8005290C` at 0x800529C8 — a block-order
   residue, not a spelling.

## func_8003062C (230) — jump table read first, drafted from the table

The case order came from `jtbl_800102AC`, not from the listing's block order:

```
index 0 -> .L80030988 (tail)      index 1 -> .L80030680 (start arm)
index 2 -> .L8003074C (sub-state) index 3, 4 -> .L80030988 (tail)
```

So the switch is on `D_8008A360` with cases 1 and 2 carrying code and 0/3/4 empty, which is what
makes gcc emit the five-entry table and the `sltiu v1, 5` range test. `D_8008A360 == -1` returns
before the switch. The start arm (case 1) is the sample-start path: sound id from a 4-entry rotation
table at `D_8008A38C`, `D_8008B0B8` updated, `func_8004FECC` → `func_80052C10` → `func_80053408`
with the `(v * 25) >> 5` volume and `func_80053014`. Case 2 is a five-way sub-state machine on
`D_8008A364` (0 = the 0x385-frame counter and the 0x2B submit id, 1/2 = the loading arm, 4 = the
0x79-frame arm), and its loading arm is the store-first shape: `func_80051574` writes its out
parameter and the code *stores* the picked index into `D_8008A388` before branching on it again.

Two transcription errors were caught by measurement, both real:

| fix | result |
|---|---|
| `if (scratch != 1 && D_8008A388 != -1) break;` read with the polarity inverted | 221/230 → 158/230 after correcting it to `&& D_8008A388 == -1`, plus separate `sel`/`cand` locals so `s1` and `s0` both exist |
| `(D_8008A36D * 25) >> 5` produced `sra`; the game has `srl` | 158 → **157/230** — the shift needed the unsigned cast |

**Park, 157/230 @0x388 (want 0x398).** Frame 0x28 with `ra/s1/s0` and the whole head match to
0x800306C4. Residues: (a) the case-2 sub-state arms are ordered differently — my build puts the
loading arm before the case-4 arm while the game puts case 4 at 0x80030928, after the loading arm's
tail; (b) 4 words short overall, all of it in the `.L80030968` continuation, which the game reaches
from two places and I inlined twice but with one fewer store. Turn-on instruction:
`lbu $a0, 0x0($gp) [D_8008A3A8]` at 0x80030970 — in the game the second `func_8004C3A4` call
re-loads the argument after the first call returns, while my draft reuses the value.

## func_8004F250 (231) — SPU sample loader, drafted whole

The body is a 0x4000-byte stack buffer loader: open via `func_800363F8(a0, 1, 0)`, read a 0x800-byte
header, take the size from `header[0xC]`, allocate the data block, read it, then either fix up the
node table (a1 != 0) or slide the node addresses by the voice's `unkC` (a1 == 0). The `0x7EFF0`
budget is `D_8008A998 = 0x7EFF0 - *(u32 *) 0x80082940 - D_8008A99C` after adding the allocation.
Three `SpuIsTransferCompleted`/`VSync` waits of 0x12C ticks guard the transfer.

The interesting decode detail: the same register carries `a2` first and then the loaded header
(`s3`), and `s5` is both the malloc'd base and the running node pointer. The 8-byte node stride is
`i << 3` off `e->unk24` in one loop and pointer arithmetic in the other.

**Park, 226/231 @0x3a4 (want 0x39c), 2 words over.** Frame 0x4038 exact, head matches except the
saved-register assignment: the game homes `a2` in `s3` and the handle in `s6`, my draft homes `a2`
in `s4`, the handle in `s7`, and spills one extra value to `fp`. That is the argument-binding class
already filed — the game reuses `s3` for the loaded header once `a2` dies, which C can express only
as an assignment to the parameter, and the file rejected that as a spelling hunt. Parked in seconds
per the standing rule. Turn-on instruction: `addu $s3, $a2, $zero` at 0x8004F260.

## State

- attempted 3 (all three written whole, measured once each plus one correction each), converted 0, parks 3
- new banked fact: the init arm of the `D_8008A9FC` dispatch stores the **mode value**, not zero —
  the previous record had this wrong, and the `sb` sits in the `memset` delay slot because the
  store is written before the call
- corrected banked fact: `func_80052874` has **no jump table**; the earlier record's turn-on
  instruction for it was wrong and is replaced above
- `pipeline:` scan 684 files 0 problems, gate 684/684, build `SLUS_009.35: OK`
- worktree check: 684 local = 684 upstream before and after the records commit
- queue: 141 open fresh, 219 attempted, 684 merged (measured before this pass's three drafts)
