#!/usr/bin/env python3
"""Undrafted-body census by size band and class. Reads only; no numbers are stored here."""
import re, sys
sys.path.insert(0, 'work')
from enumerate import bodies, drafted

SCRATCH = re.compile(r"0x1F80|%hi\(0x1F8")
GPSTUB  = re.compile(r"\blui\s+\$gp|addiu\s+\$gp,\s*\$gp")
bands = [(0,20),(21,40),(41,100),(101,200),(201,10**6)]
have = drafted()
rows = []
for n, name, text in sorted(bodies()):
    if name in have:
        continue
    cls = 'C'
    if SCRATCH.search(text):
        cls = 'scratchpad-sp'
    elif GPSTUB.search(text):
        cls = 'gp-reload'
    rows.append((n, name, cls))
print('undrafted bodies: %d (C: %d)' % (len(rows), sum(1 for r in rows if r[2]=='C')))
for lo, hi in bands:
    sub = [r for r in rows if lo <= r[0] <= hi]
    c = [r for r in sub if r[2]=='C']
    classes = {}
    for r in sub:
        if r[2] != 'C':
            classes[r[2]] = classes.get(r[2], 0) + 1
    print('%3d-%-6d total %3d  C %3d  %s' % (lo, hi, len(sub), len(c), classes or ''))
print()
print('C bodies, smallest first:')
for n, name, cls in [r for r in rows if r[2]=='C'][:40]:
    print('%3d %s' % (n, name))
