# Pass: guard the selection, then convert (29 Oct 2026)

Two jobs: make the stale-candidate defect impossible to reach by accident, then convert with the two
rules the previous pass skipped, in the order given — call signature forward from a guard first, stepped
loop with the step in the condition second — and only then classify what survives as allocation, naming
the instruction each claim turns on.

## The guard

`work/select.py` (new):

- `sync` fetches, cuts the tree to the fetched sha **in the same command**, refuses to finish unless
  `HEAD == origin/main` and `src/funcs` is clean, and records that sha in `work/.select-sha`.
- `list` enumerates open bodies only from that tree. A body whose unit file exists is merged by
  definition and is never printed; it reports how many it suppressed.
- `check` refuses a merged body, a body with no listing, a tree at another sha, or a dirty `src/funcs`.
- `draft` is the only sanctioned way to start a body: it runs `check` first and exits without writing
  anything on refusal, and it never overwrites or removes a unit file.

Proof it refuses, run in this order:

```
synced: HEAD = origin/main = 73b95a44, src/funcs clean, 674 units
REFUSED func_8002FE80: MERGED on main@73b95a44 (src/funcs/func_8002FE80.c exists)   exit 1
REFUSED func_8002BCB0: MERGED on main@73b95a44 (src/funcs/func_8002BCB0.c exists)   exit 1
select: REFUSED func_8002DDE0: MERGED on main@73b95a44 — nothing drafted              exit 1  (file untouched)
select: src/funcs has local edits, selection would be unsound: M src/funcs/func_8002FE80.c
select: tree is at 76450aac, sync recorded 73b95a44 — run sync again
```

The last two are the other ways this lane has gone wrong: a hand-edited unit file, and measuring in a
tree that had drifted off the fetched sha. Both now block drafting rather than being noticed later.
`list` on the current tree: **408 open, 674 suppressed as merged**. Drafts rejected by the guard this
pass: **3 merged + 1 dirty-tree + 1 unsynced-tree**.

## Conversions (1 of 4 drafts)

| function | result | PR |
|---|---|---|
| func_8002C490 | **MATCH** | [#194](https://github.com/andrewnakas/thrasher-skate-decomp/pull/194) |

The change: split the index arithmetic into its own statement and name the result —

```c
id = func_8002C454();
if (id != -1) {
    id = id - D_8008AFA4;
    p = D_8008AFA8 + id * 8;
    return p;
}
return 0;
```

That moved the call result into `$a0` (the game's home for it, ours had `$v1`) and let both `return 0`s
cross-jump to one epilogue with the zero in the delay slot. The permuter found the shape at base score
185; the winning output was noise-wrapped (`new_var`, `new_var2 = 1`, `-new_var2`), so the change was
rewritten as readable C and re-verified: `MATCH` before shipping. Scan 675 files 0 problems, gate
675/675, build `SLUS_009.35: OK (16829afba66533e2645bf87af2774671b06ff36b)`.

**This is the first permuter conversion on a body whose residue was a register home** — the earlier
record said the tool could not move those. It can, when the residue turns on a *statement boundary*
rather than a name: the winner's real content was one extra statement, not a rename.

## Attempts (three open, not converted), rules applied in order before any diagnosis

| function | words | rule 1 (call sig from guard) | rule 2 (step in condition) | residue |
|---|---|---|---|---|
| func_8002DD88 | 22 | `jalr` passes one arg (`a0` = object); nothing live in a1–a3 | no loop | allocation: the game's `addu $a2,$a0,$zero` at entry is absent in ours, so the object stays in `a0` and the field load lands in `$v0` instead of `$a0`. 9 of 22. |
| func_8001D4DC | 21 | no call | no loop | block layout: our switch puts the default `jr ra` inline and the shared tail later; the game orders case0 / shared tail / case1 with `j` into the tail. 19 of 21, size 0x50 vs 0x54. |
| func_8003B3CC | 19 | no call | no loop | scheduler: after the oversized-extern fix for `D_8008B3A8`, the body is instruction-identical except the delay slot after `bnez` — the game fills it with `lui $a0,%hi` and defers `addiu $v0,zero,1`; we fill it with the `addiu`. 1 word, size 0x48 vs 0x4c. |

Two levers earned their place on the way:

- **Oversized extern for an absolutely-addressed one-word global.** `D_8008B3A8` is a 4-byte slot, so
  `extern s32` gives `sw %gp_rel`; the game stores through `lui %at,%hi; sw %lo(%at)`. Declaring
  `extern u8 D_8008B3A8[0x40]` and casting at the use reproduces the game's form exactly.
- **`-mno-split-addresses` is required, not optional, on this shape.** With the flag, `base + 0xE0`
  becomes `lui $a0,%hi(sym); addiu $a0,%lo` once and the frame ends up the right size; without it the
  address folds and the body is two words short.

## The instruction-identical set, ruled out of the two rules

These five were already at instruction-identical and were re-read under both rules before being filed
as allocation. Both rules are mechanically inapplicable: `jal`/`jalr` count 0 and bare-`j` count 0 in
every one of their listings.

| function | allocation claim turns on |
|---|---|
| func_80033818 | `lw $t0,0x4($a0)` — game's first temp is `$t0`, ours `$v0` |
| func_80032CF4 / func_80032D3C | `srl $t0,$a0,30` — game `$t0`, ours `$v0` |
| func_80033E14 | `lw $t0,0x0($a0)` — game allocates twelve temps `$t0…$t9,$v0,$v1`; ours `$v0,$v1,$a2,$a3,$t0…` |
| func_80011B48 | `sll $v1,$a0,4` — game's first of two temps is `$v1`, ours `$v0` |

## Queue

`origin/main` at `73b95a44`: **674 merged unit files, 408 unmatched listings open.**
