# Store-first sweep + parameter-homing experiment, 2026-10-28 (vii)

Conversions 0, bodies attempted 4 (two twins counted as one experiment on shared code plus one
re-measure), all parks named by turn-on instruction. Pipeline green on a synced tree.

## Move 1 — the store-first sweep, selected mechanically

`work/scan_storefirst.py` finds the signature that closed `func_80047B28` from the listing alone:
a `jal`, then within five instructions a `sw $v0|$v1, off($base)` of the call's result, then
within eight instructions a `beqz/bnez` on that same register with no intervening write to it.

**Reach: 51 listings in the band carry the signature.** Intersected against a freshly synced
`select.py list --fresh`, **17 are open and never drafted**:

```
  98 func_8004AC1C    129 func_800380BC    142 func_8002BD64    151 func_80047C94
 164 func_8004966C    169 func_80015A94    215 func_80032740    230 func_8003062C
 231 func_8004F250    231 func_80052874    290 func_80023004   335 func_800235E0
 408 func_80050A3C    416 func_8005458C    470 func_80025B90   535 func_80028498
1679 func_800309C4
```

None of the four bodies worked below came from this list — they are 95–110 words and the list is
the 98-and-up framed band, so the sweep's first real test is the next pass. The selection is
mechanical and cheap; the drafting is not, which is why the lane is short of volume again.

## Move 2 — the twins, settled as far as C can settle them

`func_80017740` (95 words) and `func_80018118` (96) reach an exact size and stop at one class:
the second parameter is homed in s4 and the first in s5, the reverse of what gcc 2.8.1 emits for
our source. Five spellings were benched on 80018118, every one measured:

| # | spelling | result |
|---|---|---|
| 1 | nested `if/else` writing the flag word | 47/96 |
| 2 | default-store then `if (flag) store 1` | 9/96 |
| 3 | `flag = a1;` before the tag test | 9/96 (unchanged) |
| 4 | parameters declared `(s32 a1, s32 a0)` — the order the homes imply | **7/96, homes match, tag test wrong** |
| 5 | named copies `flag = a1; tag = a0;` in the listing's store order | 21/96 |
| 5b | same, with `tag`'s declaration before `flag`'s | 21/96 |

**What the experiment proved.** Callee-saved homing follows the *binding* of names to argument
registers, not the shape of the body: spelling 4 is the only one that reproduces
`addu $s4, $a1` / `addu $s5, $a0`, and it does so exactly because the name bound to `$a1` becomes
the first declared parameter. With the correct binding — id in `$a0`, flag in `$a1`, which the
tag test and the `sh` into the record's first field both require — gcc homes the id in s4 every
time. Spelling 5, which supplies the copies the binary actually contains, homes the flag in s4
correctly but pushes the tag into s2 and adds an instruction, landing at 21.

So the wall statement is now precise: **for these two bodies the difference is not a source
feature at all but which argument register the first callee-saved home is given, and no C
spelling that keeps the id in `$a0` moves it.** Both twins stay parked at 9/96 and 9/95 with the
turn-on instruction named (`addu $s4, $a1` at 0x80018120 / 0x80017748).

## Bodies attempted

| function | words | best | residue | turn-on instruction |
|---|---|---|---|---|
| func_80018118 | 96 | 9/96, size exact | parameter homes swapped | `addu $s4, $a1` at 0x80018120 |
| func_80017740 | 95 | 9/95, size exact | same | 0x80017748 |
| func_80053408 | 104 | 43/104 (0x19c, want 0x1a0) | arm-place polarity plus a shared tail | `bnez $v0, .L80053508` at 0x800534B8 — the non-0x200 path must fall through, which needs the `== 0` test written first *and* three call sites, not two |
| func_80029664 | 106 | 104/106 (0x1b4, want 0x1a8) | three words over; the `else if` on the two packed words duplicates instead of falling through | `beq $a2, $v1, .L8002979C` at 0x8002977C |

`func_80053408` decoded cleanly and is a good next target: the volume curve
(`s1 = a0 & 0xFF`, the other value `= ((a0 & 0xFF) * (0x7F ∓ a1)) >> 7`) is settled, the struct
at `sp+0x10` is `{u32 mask; s32 3; u16 volL; u16 volR}` at stride 0x40, and the only open question
is the arm placement of the two `SpuSetVoiceAttr` paths. Its listing is in the park.

## State

- attempted 4, converted 0, parks 4, every park carrying its turn-on instruction
- new banked selection: `work/scan_storefirst.py` — 51 listings, 17 open, for the next pass
- new banked fact: callee-saved homing follows name-to-register binding (experiment above)
- pipeline: `scan` 681 files 0 problems, `gate` 681/681, `build` `SLUS_009.35: OK
  (16829afba66533e2645bf87af2774671b06ff36b)`
- worktree check: 681 local = 681 upstream before and after the records commit this time
- queue: **141 open fresh, 219 attempted, 681 merged** on a freshly synced tree
