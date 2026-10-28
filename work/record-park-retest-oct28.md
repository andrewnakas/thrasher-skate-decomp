# Pass: re-testing the 1-6 word parks with the two new shape rules (28 Oct)

Queue unchanged: fresh `origin/main` 7e24509, 663 merged, **354** unmatched.
Parks re-tested: **6** (plus one stale). Converted: **0**.

## Per-park table (before -> after)

| park | before | rule / shape tried | after | class of the residue |
|---|---|---|---|---|
| func_80055820 | 1/34 | `-fno-schedule-insns2` (alone and with `-fno-schedule-insns`), permuter 500 compiles | 1 (flags made it 8) | **delay-slot fill**: gcc puts the second `addiu a0,0x3E8` in the `jal` slot where the game leaves `nop`. #17 class. |
| func_8002BCB0 | 2/17 | fresh local in `u16`/`u32`/`s32`; permuter (no mutation applied) | 2 | **register home**: `lhu a1` vs `lhu v0` for the tested field |
| func_8002FE80 | 2/24 | don't name the buffer pointer (cast at the store) | 2 | **register home**: `addiu a1,sp,0x10` vs `v1` for `&buf` |
| func_80056C90 | 2/36 | incomplete-array extern + cast at the use (instead of a sized array) | 2 | **address register**: `lui/addiu` both into `$t0` vs a split `lui $v1; addiu $t0,$v1` |
| func_80056FF4 | 2/39 | three address spellings for `D_8008B4DC` (cast, array-of-one, pointer) | 2 | **address register**: `lui $a0; lbu $a0` vs `lui $v0; lbu $a0` |
| func_80042E9C | 2/58 | (measured, no shape applied) | 2 | **register home** on a tested field load |
| func_80020D74 | 4/39 | base re-load rule (n/a: no base pointer), flag-loop rule (n/a: tail return) | 4 | **scheduler**: gcc hoists `lw v0,0x1C(sp)` above an independent `or` |
| func_8001DB74 | 2/26 | **offset-left address with truncated base** `(E *)(i*0x44 + (u32)D_8008AEC4)` | **MATCH** | — but the body was **already merged as #119**; the park was stale, so nothing to ship. File restored. |

## What the re-test measured

- **The offset-left/truncated-base lever works on a 2-word park** (func_8001DB74 went 2 -> 0 in one
  edit). That is the third independent confirmation of this lever, and the cheapest shape in the pool.
- **Neither of the two new framed-band rules applies to this population**: none of these parks has a
  base pointer that the listing re-loads (they load once), and none has a two-stage search loop. The
  rules were derived from 70+ word framed bodies; the 1-6 word parks are straight-line or single-loop
  bodies where the residue is a register home or a delay slot.
- **The 2-word parks are one class**: a value's register home (`v0` vs `a1`/`a0`/`t0`). Six spells
  tried across four bodies, none moved. The permuter adds nothing at this size (two of its runs
  applied zero mutations on a 17-word function).

## Process defect found and fixed mid-pass

The park list was built from `work/best/` alone, which still holds drafts for bodies that merged
after the draft was written; func_8001DB74 is one. Every candidate is now filtered against
`git ls-tree origin/main` before a shape is spent, and the one file that had been copied in was
restored with `git checkout --`.

## Count

6 parks re-tested, 0 converted. Best remaining park: func_80055820 at one word (delay slot).
