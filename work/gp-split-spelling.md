# The gp-base split spelling, 28 Oct 2026

Question: the game materialises a gp-relative base into its own register and then loads/stores through a
*displacement* of that register (`addiu $v1,$gp,%gp_rel(S); ...; lw 0x18($v0)`), where our C folds the
displacement into the address (`lui %hi(S+0x18)` / `addiu %lo(S+0x18)`). Which source form splits them?

## The experiment (each row disassembled from `build/gpN.o` with the project's own cc.py + objdump)

| form | emitted address sequence |
|---|---|
| `extern u8 S[];` then `((u32*)(S + 0x18))[i]` | `lui %hi(S+24)` `addiu %lo(S+24)` — **folded** |
| `extern u8 S[0x40];` then `((u32*)(S + 0x18))[i]` | `lui %hi(S+24)` `addiu %lo(S+24)` — **folded** |
| `extern u8 S;` then `((u32*)(S + 0x18))[i]` | `lbu $2,S` — wrong: reads the byte, not the address |
| `extern u8 S;` then `u8 *b = &S;` `((u32*)(b + 0x18))[i]` | **`addiu $2,$gp,%gp_rel(S)` ... `lw $2,24($4)`** ✓ |
| `extern u8 S;` `u32 b = (u32)&S;` `(E*)(b + i*4 + 0x18)` | `addiu $2,$gp,S+24` then `addu` — folds into the gp offset ✗ |
| `extern u32 S;` `((u32*)((u8*)&S + 0x18))[i]` | `addiu $2,$gp,S+24` ... `lw 0($4)` ✗ |
| `extern u32 S[];` then `S[i]` | `lui/addiu` absolute (not gp) ✗ |
| `u8 S[4];` defined in the same TU | `addiu $2,$gp,0` ... `lw 24($4)` ✓ |

**The spelling that works on an external symbol is: declare it one byte (`extern u8 S;`), take its address
into a pointer local (`u8 *b = &S;`), and put the displacement on the use (`b + 0x18`, or `*(E**)(b + 0x18 +
i*4)`).** A one-byte extern is gp-addressable, so `&S` becomes `addiu $x,$gp,%gp_rel(S)`; because the +0x18
is applied at the use site and not inside the `&`, gcc keeps it as the load/store displacement.

Two traps, both measured:
- folding the displacement into `&S` (`&S + 0x18`, or an integer base) moves it into the gp offset;
- keeping the pointer local alive across the function's calls gives it a **saved register** and grows the
  frame (func_800190E0 went 0x30 -> 0x34 and +2 differing words that way). Scope the base per use site.

## What it reached

| body | before | after the spelling | residue |
|---|---|---|---|
| func_800190E0 | 69/76 differ, 3 words long | **9/76 differ, size exact** | `sll` before `addiu` (2), `andi` home `$v1` vs `$a0` (2), loop-init order (4), one block (1) |
| func_8002050C | not drafted | **7/25 differ, size exact** | `sll` before `addiu` (2), `-1` materialised twice instead of copied (4), one `addu` |

Both bodies' first transcription also used prologue-first: 800190E0's 0x30 frame with s5,ra,s4..s0 and
8002050C's frameless leaf came out exact on the first try.

## The next wall, now measured twice

The `sll`-before-`addiu $gp` order is the *same* residue in both bodies: the game scales the index, then
materialises the gp base; ours materialises the base first. Every spelling tried (index-first expression,
named index local, named array local, pointer arithmetic) leaves the order unchanged, and the same is true of
the `-1` materialisation in func_8002050C. That is now a two-body-confirmed scheduler residue, not a
spelling question.

## Population

110 listings carry an `addiu $x,$gp,%gp_rel(S)` address; **58 of them are still open** against fresh
origin/main. The cheap members of that set were merged in earlier passes (all eight of the <=22-word ones),
so the open tail begins at func_8002BF9C (24 words, already parked on another residue) and runs up through
func_8001C810 (72 words): roughly half the population is 40 words or shorter, which is where the spelling
plus prologue-first should convert next.

## Queue

Fresh `origin/main` has 660 merged units; the clean enumerator against it prints **357** unmatched bodies,
185 of them never drafted (the local asm/ tree is stale and still lists 13 already-merged bodies).
