# Pass oct29b — strength-reduce flag on both fold parks, then two untouched bodies

Tree `7605c52b` (693 units, matches `origin/main`), no branch switched.

## 1. The flag, as the single variable

Both parks were re-run with `/* cflags: -fno-strength-reduce */` on line 1 and their best drafts
otherwise untouched.

| body | without flag | with flag | verdict |
|---|---|---|---|
| `func_80020608` | 119/135, 0 matching | 119/135, 0 matching | **null on size** |
| `func_8002ECB8` | 121/119, 23 matching | 121/119, 23 matching | **null entirely** |

The flag is not a no-op here — it did move `func_80020608`, just not toward the game. It restored the
clear loops' separate base add (`addu $v0,$t3,$a1` where the game has `addu $v0,$v1,$t9`, and the
displacements `3/0x28/0x2C` survived), but it simultaneously un-hoisted the *link* loops' second
pointer, costing those loops their `addu $a3,$t2,$v0` + `addu $v0,$a2,$t9` pair. Net zero: 0x1dc either
way. So the flag bites only where the induction variable is a **single scalar pointer** — the case it
closed on `func_8003031C` — and not where the loop keeps a base and an offset in two registers.

`func_8002ECB8` is byte-identical with and without the flag, which confirms its residue is not
strength reduction at all: it is `0x8002EE4C`, the shared-epilogue branch.

## 2. Two bodies written whole

**`func_8003599C`** (137 words, two 4-entry table inits, each bit-gated and dispatched on a nibble).
Written from the listing and both jump tables in one pass. 0x204 = **129/137**, 2 matching.
The switch arms were laid out in table order (case 4, 2, 7, 8, default, case 0) per the banked rule.
Residue: the first `-1` fill loop's `i + 0` index (the game keeps a second zero register, `addu $v0,$a0,$t1`
with `$t1` separate) and the call setup around the two dispatch blocks.
Turn-on: `0x800359F0`.

**`func_80034874`** (129 words, text primitive walker over `D_800A5634`).
Written whole from the listing without a prior decode pass. **128/129 words, 31 matching**, but the
frame is 0x70 against the game's 0xC0 — the two stack records at `0x28` and `0x30` and the limit at
`0x90` have to be named as the structs the listing indexes, not as one byte buffer with offsets.
Park with turn-on `0x80034874` (frame size, so no shape will close it before the records are named).

## Count

conversions **0**, bodies measured **4** (2 flag re-tests, 2 fresh writes). No PR.

Queue at `7605c52b`: 74 open (fresh), 238 attempted, 693 merged units.

## What this proves for the next pass

The flag lever is **spent**: it converts on variable-pointer loops only, and both remaining fold parks
are two-register-base loops it does not touch. The next pass should stop re-testing it and go back to
fresh bodies, where `func_80034874`'s 31 matching words at exact size-less-one is the best signal in
three passes and needs only its stack records named.
