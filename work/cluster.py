"""Cluster unopened bodies by disassembly shape.

A body's shape is its instruction stream with these normalised away:
  * memory displacements          -> <off>       (struct offsets differ per family member)
  * %hi/%lo/%gp_rel symbols, D_*/func_* operands, branch targets -> <sym>/<tgt>
  * register identity             -> $Aa..$Zz in order of first appearance
  * (relaxed tier only) immediates -> <imm>      (constant-operand siblings)

Two clustering tiers are reported, because exact-stream equality is too strict to find
families and similarity is too loose to trust by itself:
  strict  - identical normalised stream
  family  - difflib ratio >= THRESH over the strict stream, greedy leader clustering

Because the small bodies are all drafted, the useful question is not "which unopened bodies
resemble each other" (nothing does: 310 bodies, median 102 instructions, one exact twin) but
"which unopened body resembles a body already matched in src/funcs" - that is the case the
session's twin matches actually were, and the template there is a merged C file.

Three views:
  corpus  - every game body (matched, parked, unopened) clustered together; families with an
            unopened member and a matched member are template instantiations waiting to happen
  opened  - the same restricted to unopened bodies (reports how little self-similarity there is)

Usage: .venv/bin/python work/cluster.py [--json out.json] [--thresh T]
"""
import csv, os, re, glob, collections, sys, json, difflib

INS = re.compile(r'/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\S+)\s*(.*)')
BR = re.compile(r'^(b|beq|bne|beqz|bnez|bgez|bgtz|blez|bltz|bal|j|jal|jalr|jr)$')
REG = re.compile(r'^\$[a-z0-9]+$')
IMM = re.compile(r'^-?(0x[0-9A-Fa-f]+|\d+)$')
THRESH = 0.80


def bodies():
    rows = list(csv.DictReader(open('config/functions.us.csv')))
    drafted = set()
    for f in glob.glob('work/*.c') + glob.glob('work/near-miss/*.c'):
        m = re.search(r'func_([0-9A-Fa-f]{8})', os.path.basename(f))
        if m:
            drafted.add('func_' + m.group(1).upper())
    out = []
    for r in rows:
        a = int(r['addr'], 16)
        if a > 0x80058633:
            continue
        n = 'func_%08X' % a
        if os.path.exists('src/funcs/%s.c' % n) or n in drafted:
            continue
        p = 'asm/nonmatchings/game/%s.s' % n
        if not os.path.exists(p):
            continue
        txt = open(p).read()
        if 'glabel' not in txt:
            continue
        if re.search(r'\b(mtc2|mfc2|ctc2|cfc2|lwc2|swc2|gpf|gpl)\b', txt) or 'Handwritten' in txt:
            continue
        out.append((n, p))
    return out


def shape(path, mask_imm=False, opcode_only=False):
    regmap = {}

    def canon(reg):
        if reg not in regmap:
            i = len(regmap)
            regmap[reg] = '$' + chr(ord('A') + i // 26) + chr(ord('a') + i % 26)
        return regmap[reg]

    toks = []
    for line in open(path):
        m = INS.search(line)
        if not m:
            continue
        mn, rest = m.group(1), m.group(2).strip()
        is_branch = bool(BR.match(mn))
        ops = []
        for op in ([o.strip() for o in rest.split(',')] if rest else []):
            mem = re.match(r'^(.*)\((\$[a-z0-9]+)\)$', op)
            if mem:                                   # displacement(base)
                ops.append('<off>(' + canon(mem.group(2)) + ')')
            elif REG.match(op):
                ops.append(canon(op))
            elif is_branch:                            # targets are addresses
                ops.append('<tgt>')
            elif IMM.match(op):
                ops.append('<imm>' if mask_imm else op)
            else:                                      # symbol operand
                ops.append('<sym>')
        toks.append(mn if opcode_only else mn + (' ' + ', '.join(ops) if ops else ''))
    return tuple(toks)


def corpus():
    """Every game body with a listing, tagged matched / drafted / unopened / skipped."""
    rows = list(csv.DictReader(open('config/functions.us.csv')))
    drafted = {}
    for f in glob.glob('work/*.c') + glob.glob('work/near-miss/*.c'):
        m = re.search(r'func_([0-9A-Fa-f]{8})', os.path.basename(f))
        if m:
            drafted['func_' + m.group(1).upper()] = f
    out = []
    for r in rows:
        a = int(r['addr'], 16)
        if a > 0x80058633:
            continue
        n = 'func_%08X' % a
        p = 'asm/nonmatchings/game/%s.s' % n
        if not os.path.exists(p):
            continue
        txt = open(p).read()
        if 'glabel' not in txt:
            continue
        if os.path.exists('src/funcs/%s.c' % n):
            tag = 'matched'
        elif re.search(r'\b(mtc2|mfc2|ctc2|cfc2|lwc2|swc2|gpf|gpl)\b', txt) or 'Handwritten' in txt:
            tag = 'skipped'
        elif n in drafted:
            tag = 'drafted'
        else:
            tag = 'unopened'
        out.append((n, p, tag))
    return out


def callees(path):
    """Set of jal targets - the semantic family key.

    Shape similarity (above) only groups bodies of near-identical length; the families that
    actually share a template in this codebase differ in length but call the same helper set
    (the table-manager bodies all call func_80015E8C/15F10/19518/1954C, whether they are
    0xE0 or 0x4D4 bytes long).
    """
    return frozenset(re.findall(r'jal\s+(func_[0-9A-F]{8})', open(path).read()))


def clusters(items, keyfn):
    groups = collections.defaultdict(list)
    for n, it in items:
        groups[keyfn(it)].append(n)
    return groups


def opcount(shape_tokens):
    c = collections.Counter(t.split(' ')[0] for t in shape_tokens)
    return c


def family_clusters_fast(items, thresh=THRESH):
    """Leader clustering with a cheap prefilter.

    difflib over 1235 bodies of ~100 instructions is O(n^2 * len) and does not finish, so
    candidates are blocked twice first: same instruction-count band, then an opcode-multiset
    Jaccard >= 0.85. Only survivors get a real difflib ratio.
    """
    n = len(items)
    counts = [opcount(s) for _, s in items]
    sizes = [len(s) for _, s in items]
    band = collections.defaultdict(list)
    for i, sz in enumerate(sizes):
        band[round(sz / 8)].append(i)

    cand = collections.defaultdict(dict)          # i -> {j: ratio}
    for b, idxs in band.items():
        pool = idxs + band.get(b + 1, []) + band.get(b - 1, [])
        for x in idxs:
            for y in pool:
                if y <= x:
                    continue
                if abs(sizes[x] - sizes[y]) > max(4, 0.15 * max(sizes[x], sizes[y])):
                    continue
                a, c2 = counts[x], counts[y]
                if len(a) > len(c2):
                    a, c2 = c2, a
                inter = sum(min(v, c2[k]) for k, v in a.items() if k in c2)
                tot = sizes[x] + sizes[y]
                if 2.0 * inter / tot < 0.85:
                    continue
                r = difflib.SequenceMatcher(None, items[x][1], items[y][1], autojunk=False).ratio()
                if r >= thresh:
                    cand[x][y] = r
                    cand[y][x] = r

    leaders = []                                   # [lead_index, [member indices]]
    owner = {}
    order = sorted(range(n), key=lambda i: (-len(cand[i]), items[i][0]))
    for i in order:
        if i in owner:
            continue
        lead = i
        members = [i]
        owner[i] = lead
        for j, _r in sorted(cand[i].items(), key=lambda kv: -kv[1]):
            if j not in owner:
                owner[j] = lead
                members.append(j)
        leaders.append((items[i][0], items[i][1], [items[m][0] for m in members]))
    return sorted(leaders, key=lambda x: (-len(x[2]), x[2][0]))


def family_clusters(items, thresh=THRESH):
    """Greedy leader clustering: each body joins the first leader it is >= thresh similar to."""
    leaders = []                                  # [(member_addr, shape_tuple, [members])]
    for n, s in items:
        best, best_r = None, 0.0
        for lead in leaders:
            r = difflib.SequenceMatcher(None, lead[1], s, autojunk=False).ratio()
            if r > best_r:
                best, best_r = lead, r
        if best is not None and best_r >= thresh:
            best[2].append(n)
        else:
            leaders.append((n, s, [n]))
    return sorted(leaders, key=lambda x: (-len(x[2]), x[2][0]))


def report(tag, items, thresh):
    fam = [f for f in family_clusters(items, thresh) if len(f[2]) > 1]
    print('\n=== %s: %d families at ratio >= %.2f' % (tag, len(fam), thresh))
    for lead, s, members in fam:
        tags = collections.Counter(tags_of[m] for m in members)
        if len(members) < 2:
            continue
        print('   %2d  lead %s  %s' % (len(members), lead, ' '.join(members)))
        print('        ' + ' / '.join('%s %d' % (k, v) for k, v in sorted(tags.items())))
    return fam


def report_callees(cor, top=20):
    groups = collections.defaultdict(list)
    for n, p, t in cor:
        k = callees(p)
        if k:  # a body with no calls has nothing to share; frozenset() would join them all
            groups[k].append((n, t))
    ranked = sorted(groups.items(), key=lambda kv: (-len(kv[1]), kv[1][0][0]))
    live = [kv for kv in ranked if any(t == 'unopened' for _, t in kv[1])
            and any(t == 'matched' for _, t in kv[1])]
    print('\n=== callee-set families: %d families, %d with an unopened body and a matched template'
          % (len(ranked), len(live)))
    for k, mem in ranked[:top]:
        if len(mem) < 2:
            continue
        c = collections.Counter(t for _, t in mem)
        print('  %2d  %s' % (len(mem), ' / '.join('%s %d' % (a, b) for a, b in sorted(c.items()))))
        print('      ' + ' '.join('%s%s' % (n, '' if t == 'drafted' else '(' + t[0] + ')')
                                  for n, t in mem[:12]))
    return ranked


def main():
    global tags_of
    thresh = float(sys.argv[sys.argv.index('--thresh') + 1]) if '--thresh' in sys.argv else THRESH
    cor = corpus()
    tags_of = {n: t for n, p, t in cor}
    ci = [(n, shape(p)) for n, p, t in cor]
    print('corpus: %d bodies (%s)' % (len(ci), ', '.join('%s %d' % (k, v)
          for k, v in sorted(collections.Counter(t for _, _, t in cor).items()))))
    fam = report('corpus', ci, thresh)
    report_callees(cor)
    inst = [f for f in fam if any(tags_of[m] == 'matched' for m in f[2])
            and any(tags_of[m] == 'unopened' for m in f[2])]
    print('\ntemplate families (matched member + unopened member): %d, holding %d unopened bodies'
          % (len(inst), sum(sum(1 for m in f[2] if tags_of[m] == 'unopened') for f in inst)))
    if '--json' in sys.argv:
        out = sys.argv[sys.argv.index('--json') + 1]
        json.dump([{'lead': l, 'members': [(m, tags_of[m]) for m in mem], 'len': len(s)}
                   for l, s, mem in inst], open(out, 'w'), indent=1)
        print('wrote %s' % out)
    return
    bl = bodies()
    items = [(n, shape(p)) for n, p in bl]
    print('unopened clean bodies: %d' % len(items))

    strict = clusters(items, lambda s: s)
    multi = {k: v for k, v in strict.items() if len(v) > 1}
    print('strict: %d distinct shapes, %d exact-twin clusters holding %d bodies'
          % (len(strict), len(multi), sum(len(v) for v in multi.values())))
    for k, v in sorted(multi.items(), key=lambda kv: -len(kv[1])):
        print('   %2d  %s' % (len(v), ' '.join(v)))

    fam = family_clusters(items)
    fam = [f for f in fam if len(f[2]) > 1]
    print('\nfamily (ratio >= %.2f): %d clusters with >1 member, %d bodies in families'
          % (THRESH, len(fam), sum(len(f[2]) for f in fam)))
    for lead, s, members in fam[:15]:
        print('   %2d  lead %s  %s' % (len(members), lead, ' '.join(members[1:9]) +
                                       (' ...' if len(members) > 9 else '')))
        print('        ' + ' | '.join(s[:5]) + (' ...' if len(s) > 5 else ''))

    if '--json' in sys.argv:
        out = sys.argv[sys.argv.index('--json') + 1]
        json.dump({'families': [{'lead': l, 'members': m, 'len': len(s)} for l, s, m in fam]},
                  open(out, 'w'), indent=1)
        print('\nwrote %s' % out)


if __name__ == '__main__':
    main()
