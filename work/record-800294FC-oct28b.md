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
