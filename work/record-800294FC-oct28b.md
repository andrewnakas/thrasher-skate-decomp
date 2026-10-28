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

## 2. func_8001B238 — parked, own-rodata addressing, 58/90, size 0x164 vs 0x168

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

**Remaining blocker, precise:** this function owns 8 bytes of rodata at `0x80010668`/`0x8001066C`
(`config/functions.us.csv` row has `rodata_addr=80010668`). The game addresses each word absolutely:

```
8001B2C0 lui a1, %hi(D_8001066C)
8001B2C4 lw  a1, %lo(D_8001066C)(a1)
```

Our compiler puts two 4-byte `static const u32` into small data and emits `lw a1, 0x4($gp)` (no symbol) —
4 of the 58 differing words, and the reloc cannot even be named. `-G8` is the pinned flag and `-G0` would
break the three `%gp_rel` data globals the game does use in this same function. A spelling that keeps small
*data* gp-relative while forcing *rodata* absolute is the missing piece; it is a compact, self-contained
experiment (10-line bench, two consts, emit asm) and it would likely close several bodies, since this is the
first body seen whose own rodata is addressed absolutely while its data is gp-relative.

The other one word is the `nop` after the case-0 guard's `nop` slot.

Drafts kept: `work/best-294FC-v3.c` (+ the for-init move), `work/best-8001B238-v2.c`.

## Next pass should

1. Run the 10-line rodata bench: `static const u32` vs `extern const u32` + definition vs a struct wrapper vs
   `-fno-...` spellings, emit asm, find the one that gives `lui/%lo` for each word while 4-byte *data* stays
   `%gp_rel`. Then finish func_8001B238 from `work/best-8001B238-v2.c`.
2. Apply the two new levers on the next band members *during* the first transcription: for-init walking
   pointers, and store-before-call for any parameter that reaches memory.
