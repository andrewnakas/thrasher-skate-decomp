# Fresh band, five framed bodies: no conversions, and what stopped each, 2026-10-28 (g)

Branch `freebuff/records-oct26`, work cut from `origin/main@aa8fe7a6` (680 units) via `lane/select.py sync`.
Candidates: `lane/select.py list --min 70 --fresh`, ascending size. The two bodies my own unmerged PRs
cover (func_8004B088, func_8001E3A0) are still on the fresh list because neither is merged; they were
skipped, not re-drafted.

**Conversions: 0. Attempts: 5.** Queue: **680 merged on main + 2 in review (#199, #200), 401 open**
(399 once those land). Pipeline green at 680 units: scan 680 / 0 problems, gate 680/680, build PASS
`16829afba66533e2645bf87af2774671b06ff36b`.

## Per-body table

| function | words | best | outcome / turn-on |
|---|---|---|---|
| func_800290CC | 84 | 48/84 (0x154, want 0x150) | parked — the game reuses `$s0` (the callee's result) for `out+4`, so five live values fit six saves; with the two-pointer shape ours needs `$s5`, and the folded single-pointer shape leaves one word of motion (`addu $s2,$v0` placed before the store instead of in the `bltz` slot) |
| func_80048208 | 89 | 33/89 (size equal) | parked — the jump table, the empty `case 3`, the cross-jumps and the `if (v == 0) return 1` block all line up; the residue is pure register rotation: game `h`→`$s0`, `size`→`$s1`, `r`→`$s2`, `buf`→`$s3`; ours `h`→`$s1`, `size`→`$s0`, `r`→`$s3`, `buf`→`$s2` |
| func_8002B3FC | 90 | 82/90 (0x150, want 0x168) | parked — the game keeps a 12-byte vector at `0x20` and copies it into the outgoing argument area at `0x10` before passing its address in `$a0` (struct by value); ours folds the two blocks into one, so the frame is 0x38 against 0x48 |
| func_80039BB4 | 90 | 88/90 (0x130, want 0x168) | parked — the four clamps are the gap: the game spends ~9 words per clamp (`sltiu` / `beqz` / `sltiu` / `blez` / `bnez` / `j` / `addiu`), our `if (x > hi) x = hi; else if (x <= 0) x = 0;` spends ~6, leaving 14 words short |
| func_80041538 | 92 | 68/92 (0x150, want 0x170) | parked — the array-base address form (`addiu $a0,$gp,%gp_rel(D_8008B364)` in the game vs `lui/addiu` for our `extern u32 []`) plus a two-store pair to `D_8008B350` (`= base` then `= rec`) that gcc drops as a dead store |

## The three short levers: no hits this pass

1. **unsigned local for an unsigned immediate compare** — not exercised: none of the five puts a masked
   value against an immediate.
2. **negated field as an unsigned load + `(s16)` at the call site** — not exercised; no negated field in
   these bodies.
3. **frame one block too large ⇒ look for invented arguments** — not exercised in that direction, but the
   inverse showed up: func_8002B3FC is a frame one block too *small* because a by-value struct argument's
   caller-side copy is folded away (0x38 against 0x48). Folding `&v` and casting `*(V3 *) &v` both still
   folded; the two-block shape was not reachable this pass.

## Facts worth keeping

- **The arm layout follows the source's case order, not the jump table's.** func_80048208's table is
  `[case1, case2, default, case4, case5]`, but the *code* order is case1, case5, case2, case4. Writing the
  cases in numeric order gave 0x148 against 0x164 (7 words short); writing case 5 immediately after case 1
  gave the exact size and 33/89 with only the register homes left. The empty `case 3: break;` is still
  required for the table to be emitted at all.
- **`sw $reg, frame_size($sp)` is a spill into the incoming argument area**, not a local. func_80047B28 has
  its 0x80-byte local buffer filling the frame, so gcc spills a stack-passed value into the incoming arg
  slot at `0xA8($sp)` — a 5th argument exists there, which is why a four-argument reading of that body
  cannot work. Not drafted this pass; the fact is the useful part.
- **A gp-relative base computed with `addiu $a0,$gp,%gp_rel(sym)` means the source indexes a scalar, not
  an array.** func_80041538 wants `(&D_8008B364)[i]` with `extern u32 D_8008B364;`; declaring
  `extern u32 D_8008B364[]` produces the absolute `lui/addiu` pair instead. This is the offset-left gp rule
  in reverse, and it did not close the body on its own (68/92 with it).

## Worktree soundness

The assertion from last pass is **still not on main** (`lane/select.py` there has `sync/check/list/draft`
but no `verify`); it is PR #196. So this pass used the equivalent inline check before and after every
checkout, and after `sync`:

```
$ for f in $(git ls-tree -r --name-only origin/main -- src/funcs); do [ -f "$f" ] || echo "MISSING $f"; done
(missing=0)
$ git status --porcelain -- src/funcs | grep -v '^??'
(none)
$ ls src/funcs/*.c | wc -l ; git ls-tree -r --name-only origin/main -- src/funcs | wc -l
680 / 680
```

No file went missing this pass; every draft was moved into `work/pass-oct28/` before any branch move.
