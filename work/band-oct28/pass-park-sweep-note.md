# Pass: park sweep at two to six words, plus the allocation filing

Date: 2026-10-28. Re-tested the whole recorded pool at <= 6 differing words with the two branch-polarity
rules from the previous pass, then filed the allocation class. All "before" numbers were re-measured
against freshly fetched `origin/main` before any shaping; three of the pool had already merged
(`func_8001F4E8`, `func_80021B74`, `func_8002D904`) and were dropped without being decoded.

## Per-park table

| function | before | after | verdict |
|---|---|---|---|
| `func_8002FE80` | 2 of 24 | **MATCH** | **argument lever** — `func_8002FEE0` takes the stack buffer as arg 1 |
| `func_8002BCB0` | 2 of 17 | **MATCH** | **argument lever** — the indirect callback takes the guard value as arg 1 |
| `func_8004DA90` | 2 of 88 | **MATCH** | **argument lever** — `func_80032DCC` takes the guard's second word as arg 1 |
| `func_80055820` | 1 of 34 | 1 of 34 | scheduler: the game leaves `nop` in a `jal` slot where we put `addiu` |
| `func_8003BF7C` | 2 of 79 | 2 of 79 | address temp register for `D_8008ACA0` |
| `func_80056C90` | 2 of 36 | 2 of 36 | `lui`/`addiu` split across two registers vs one |
| `func_80042E9C` | 2 of 58 | 2 of 58 | dead compare value in `a1` vs `v0`; not an argument, nothing live after |
| `func_80020D74` | 4 of 39 | 4 of 39 | `or` hoisted ahead of a stack load |
| `func_8002050C` | 4 of 25 | 4 of 25 | allocation (`a3` set from `v0` vs `-1`, one `andi` slot) |
| `func_8003BDB8` | 6 of 31 | 6 of 31 | allocation |
| `func_800257A0` | 6 of 21 | 5 of 21 | **`-fno-strength-reduce`** removed the pointer re-anchoring; the last 5 are the pointer copy hoisted over the guard |
| `func_80057090` | 5 of 92 | 5 of 92 | allocation |
| `func_80034B98` | — | **MATCH** | byte-exact, blocked only by `config/` (#101); not shippable from this lane |

Conversions: **3 of 13 re-tested parks.** Attempts: 13.

## Lever 1 — the argument lever (three for three)

A value the game keeps in an argument register (`$a1` here) across a guard and that is still live at a
later call is that call's argument; the draft is missing a parameter. The test is mechanical: read the
listing forward from the guard, and if the register is not reloaded before the `jal`, the call takes it.

    func_8002FE80:  extern s32 func_8002FEE0(u8 *self, u8 *buf);     /* *out = buf; return f(self, buf) */
    func_8004DA90:  extern s32 func_80032DCC(s32, s32);              /* f(v[1], v[2]) inside the guard  */
    func_8002BCB0:  extern void (*D_8008A318)(s32, u32);             /* f(t->f18, n) where n was the guard */

Two of the three also need the value **named** so the load lands at the guard rather than being
re-materialised at the call: `u16 n = t->f24;` then `if (n != 0 && ...) f(t->f18, n)`. Passing the field
expression twice makes gcc reload it and costs two words.

This subsumes part of what the lane has been calling "the allocation class". Every one-register park in
the table was checked with it first; the ones that remain are not arguments.

## Lever 2 — `-fno-strength-reduce` for a re-anchored induction pointer

Symptom in the diff: `addiu $v1, $a0, 0x74` here against `addu $v1, $a0, $zero` in the game, with every
subsequent access negative (`-0x6E`, `-0x70`, `-0x8`, `-0x4`, `0x0`) where the game uses positive
displacements. The pinned gcc anchors the loop pointer at the largest displacement. `-fno-strength-reduce`
on line 1 restores the game's positive offsets (`func_800257A0`, 6 -> 5 of 21). It does not affect the
unrelated order residue that remains.

The two branch-polarity rules from the previous pass were applied where a park had guards to re-shape
(`func_8002BCB0` in three forms, `func_80042E9C`, `func_800257A0` in two forms): neither moved the
residue. They remain right, but they are not what was holding this pool back — the argument lever was.

## Permuter, used only as the last resort

`func_80055820` was the only park to reach one differing word, so it was handed over: 150 s, 2236
reproductions, base score 200, minimum score 200, no move. Its residue is a delay-slot filler, which is
the one thing the operator set cannot reach: it can reorder statements, it cannot make gcc leave a hole.
That is the fourth pass in which the tool has returned its starting score.

## Filing

Opened **#191** — "One register home separates 11 unit bodies from matching; C cannot express it". It
carries the per-body table, the two measured permuter runs (base == minimum at both 16 words and 2
words), the argument-lever correction, and the three capabilities that would close the class, and
cross-references #17, #179, #46, #76 and #101. No protected path was touched.

## Shipped

- `func_8002FE80` — PR #188
- `func_8004DA90` — PR #189
- `func_8002BCB0` — PR #190

All three verified with `scan.py`, `gate.py` and `build.py`; image sha1 `16829afb…` unchanged, which is
the point: replacing the slab with matching C must not move a byte.

## Queue

670 merged units on `origin/main` at the start of the pass, 673 now (two of this pass's units merged while
it ran); 409 unmatched listings open, with `func_8004DA90` still in review (PR #189).
