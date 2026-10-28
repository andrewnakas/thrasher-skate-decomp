# Condition-step signature pass, 2026-10-28

Selection done once, mechanically, and the **whole list** filtered against freshly fetched
`origin/main` before any body was decoded (`git cat-file -e origin/main:src/funcs/<name>.c`
for every hit).

## The signature, measured three ways

| definition | bodies | open on main | smallest open |
|---|---|---|---|
| `j` with any `addiu` in its delay slot, target is a compare+branch block | 47 | 45 | 56 words |
| same, delay slot is a **self**-increment (`addiu $r,$r,imm`) | 24 | 22 | 56 words |
| same, and **exactly one** `j` targets that test | 18 | 16 | **90 words** |

The third row is the honest one, and the drop from row 2 to row 3 is the finding:
**a `j` carrying a self-increment is only the loop-entry rotation when a single `j` targets that
test. When several `j`s converge on it, they are switch arms and the incremented register is the
record pointer walked by the increment clause, not a step inside the condition.** The one body
that converted with this fact (func_8002DDE0, 14 words) was the last small single-entry case;
under the strict reading the smallest remaining body is 90 words.

## Bodies decoded (4)

| body | words | verdict |
|---|---|---|
| func_8001F9D0 | 59 | not the signature: the `j` delay slot carries `addiu s1,s2,0x3E`, an **initialisation**, not a step. Decoded as a string-writer loop with 5 calls; not drafted |
| func_80022F24 | 56 | switch dispatch over 0x28-byte records; **drafted, 3 shapes** |
| func_80035D2C | 69 | four-iteration loop, `s1[3]>>4` selecting three calls plus a table store of -1; decoded, not drafted |
| func_800294FC | 90 | record builder: `func_8001D5B0(…, 0x53565053, 1)`, `func_80034C20(count*28)`, then a record loop with kind = `(f4 \|\| f8) ? 0x70 : 0x6C` and a four-word inner copy; decoded, not drafted |

## Conversions: 0 of 1 measured (3 of 4 decoded)

func_80022F24 across three shapes: 44/56 at 0xe8, 45/56 at 0xe8, **45/56 at 0xe4 vs 0xe0** with
the do-while form. The remaining single word is the loop step's placement: the game's switch
arms all `j` to the continuation carrying `addiu s0,s0,0x28` (the record advance) and increment
the counter at the test, while every spelling tried puts the counter increment in the `j` delay
and the record advance at the body end, one word later.

**Class: switch-arm continuation + loop-step placement (1 word).**

Draft kept at `work/band-oct28/func_80022F24-s3.c`.

## Queue

`origin/main`: 664 merged, 418 unmatched of 1082 game functions. The condition-step signature
adds 16 targets, all 90 words or larger and all carrying calls; its small end is exhausted.

Pipeline green on this branch: scan 0/647, GATE PASS, BUILD PASS.
