# Rotation band, deep pass — 2026-10-28 (second half)

Two bodies worked in depth. **0 conversions.** Both are recorded with their exact remaining difference and
their reproduce commands, because both taught a lever the next pass can use without re-deriving.

Queue at `origin/main` `40407de`: **667 merged / 415 unmatched** of 1082 game functions; this lane
(`0x80011B48`–`0x80034FFF`) 224 of 590 unmatched.

---

## 1. func_800294FC — parked, backend class, 71/90, size 0x158 vs 0x168

Full decode, combination table and the four missing words are in `work/verdicts-800294FC.md`.

**Lever proved here (new, by emitted assembly): the walking pointer belongs in the `for`-init clause.**

```c
for (sp = (u8 *) src + 0xC, i = src->count - 1; i >= 0; i--) {
```

Moving `sp = (u8*)src + 0xC` out of the statement before the loop and into the init clause changed three
things in one step: the pointer build moved from right after the `jal` into the `bltz` delay slot (where the
game has it), the pointer took `$t1` and the countdown `$t2` (the game's assignment, previously swapped), and
the loop step came out in the game's order `a2, t0, a3, i--, bgez, sp += 0x18(delay)`.

Also measured here, negative result worth not repeating: **7 permutations of the local declaration order
changed nothing.** gcc 2.8.1 numbers temps by first use, not declaration.

Residue: 4 words of backend — `addu t3,v1,zero` (address-materialisation copy), a load-delay `nop`, and the
kind block's branch-arm layout (game 10 words with a `j` and a duplicated `0x70`; ours 8 with the false arm as
fall-through, for eight different spellings of the same value).

## 2. func_8001B238 — parked, branch form, 47/90, size 0x174 vs 0x168

90-word two-arm body: `mode` 0/1, each arm runs `memset` + two `func_8001B1CC` + the three PsyQ critical
section calls, then a shared tail comparing a pointer against an expected address.

**Lever proved here (new, by emitted assembly): store a variant/`mode` value into its global *before* the call,
and the parameter stays in a temp.**

`D_8008A088 = mode; memset(...)` instead of `memset(...); D_8008A088 = mode;` removed the whole saved-register
pair: the parameter then lives in `$a3` (the game's register) instead of `$s0`, the prologue drops from
`sw $s0 / addu $s0,$a0` to plain `addu $a3,$a0`, and the epilogue drops `lw $s0`. Score went 87 -> 58 and the
frame from 0x158 to 0x164. This is a prologue-first lever with a mechanical test: *if a parameter is stored to
memory anywhere in the function, put that store before the first call after which the source no longer needs
the parameter.*

Also measured: `switch (mode) { case 0 … case 1 … default: return 1; }` (not an `if`/`else if` chain) is what
makes gcc emit the default's `j` before both bodies — with the if-chain the same body came out 87/90 with a
saved register even after the store fix landed elsewhere.

**The rodata spelling, found and proved (new banked fact):**

```
static const u32 __attribute__((section(".rodata"))) D_80010668 = 0x8008B4F4;
```

Plain `static const u32` is 4 bytes and goes to small data, so the compiler emits `lw a1, 0x4($gp)` — a
gp-relative load with no symbol, which the game never uses for rodata. Adding the explicit section makes the
same two words absolute:

```
lui a1, %hi(D_8001066C) ; lw a1, 0x4(a1)      (ours, anchored on D_80010668)
lui a1, %hi(D_8001066C) ; lw a1, %lo(D_8001066C)(a1)     (game)
```

This moved the body 58 -> 47 differing words. The residual reloc difference is that gcc anchors both words on
`D_80010668` and uses `+4` for the second, where the game names each symbol; `-G0` is not the answer (it would
break the three `%gp_rel` data globals the same function uses).

**Remaining 3-word surplus and the branch forms:**

- case-1 guard: game `beq v0,$a3 → tail` with `addu v0,$zero,$zero` in the delay slot (4 words); ours
  `bne v0,$a3 → +3` + `nop` + `j` + `addu v0,$zero,$zero` (6 words). Polarity inversion.
- shared tail: game `bne v1,v0 → epilogue` + `addiu v0,$zero,1` + `addu v0,$zero,$zero` (3 words); ours
  compiles `return have != want` branchlessly as `xor v0,v0,v1` + `sltu v0,$zero,v0` (2 words). Writing it as
  `if (have != want) return 1; return 0;` produced the same branchless form.

Drafts kept: `work/best-294FC-v3.c` (+ the for-init move), `work/best-8001B238-v3.c` (47/90).

## Next pass should

1. Finish func_8001B238 from `work/best-8001B238-v3.c`: the rodata form is solved, what is left is 3 words of
   branch form — invert the case-1 guard so the return-0 lands in the `beq` delay slot, and find the spelling
   that makes the shared tail a `bne` + two constant loads rather than `xor`/`sltu`.
2. Apply the two new levers on the next band members *during* the first transcription: for-init walking
   pointers, and store-before-call for any parameter that reaches memory.

---

# Second half — the finishing pass

## func_8001B238: 47 -> 45, size 0x174 -> 0x170 (2 words over). Parked.

Shapes measured this pass, all with the rodata section spelling in place:

| shape | result |
|---|---|
| guard operand swap (`D_8008A088 == mode`) | 47 / 0x174 |
| case-1 body wrapped in `if (mode != …)` | 66 / 0x174 |
| tail `if (have == want) return 0; return 1;` | 47 / 0x174 |
| tail `return have == want ? 0 : 1;` | 47 / 0x174 |
| tail `switch (have != want)` / `switch (have == want)` | 47 / 0x174 |
| tail arms assigning a local, single return | 47 / 0x174 |
| `have`/`want` as `u32 *`, pointer compare | 45 / 0x170 (same as best) |
| **both guards `goto ret0`, label before the tail's `return 0`** | **45 / 0x170, best** |
| `-fno-schedule-insns2` | 52 / 0x170 |
| `-fno-schedule-insns` | 69 / 0x16c (1 word over, everything else wrecked) |
| `-fno-strength-reduce` | 45 / 0x170 (no change) |

**Lever found here: guards that return the same constant belong on a shared `goto` label.**
Writing both early exits as `goto ret0;` with `ret0:` on the tail's `return 0;` is what turned the case-1
guard from `bne` + `nop` + `j` + `addu` (6 words) into `beq $v0,$a3` with the zero in its delay slot
(4 words), and took the body 0x174 -> 0x170.

**Residue, exact (2 words):** the tail's `return 1` constant is pulled into *each* incoming jump's delay slot
(`j …` / `addiu $v0,$zero,1` at 0x1B30C in case 0), which pushes that case's `addiu $v0,$v0,%lo(D_800B9390)`
into the stream. The game has the address `addiu` in the jump's delay slot and materialises the `1` once, in
the tail's `bne` delay slot (0x1B388). Our `bne` delay slot holds a `nop`. That is `reorg`'s delay-slot fill
choice, the same class as the record's existing "a `jal` slot filled where the game leaves `nop`" note.

## func_8002AEF4: MATCH, first transcription — PR #184

91-word band member, seven calls, frame 0x38 with `ra` + `s0` (s0 = the single argument). Prologue-first, then
the whole body off the listing: two early returns, three `(s32)(s16)` halfword-shifted stack words built
before the first call, a three-word copy for the second, three `andi`-guarded flag writes through a pointer
returned by a call, and a final guarded call. It matched as written — no shape iteration.

Verified: `scan: 668 files, 0 problems`; `gate: 668/668, GATE PASS`; `build: SLUS_009.35: OK
(16829afba66533e2645bf87af2774671b06ff36b)`, objdiff reports every unit file a 100% match.

Queue after #184 lands: **668 merged / 414 unmatched** of 1082 (this lane 223 of 590).
