import sys, re, difflib
sys.path.insert(0, "tools")
import match as M

def toks(ins):
    m = re.match(r"([a-z0-9.]+)\s*(.*)", ins.strip())
    op, rest = m.group(1), m.group(2)
    # keep structure: register/immediate classes, drop register names/numbers
    rest = re.sub(r"\$[a-z0-9]+", "$r", rest)
    rest = re.sub(r"0x[0-9A-Fa-f]+|\b\d+\b", "N", rest)
    return f"{op} {rest}"

name = sys.argv[1]
addr = int(name.split("_")[1], 16)
row = M.func_row(name)
rb = M.rodata_base(row)
t = M.read_obj(M.Path("build/match/target") / f"{name}.o", name, addr, rb)
o = M.read_obj(M.Path("build/match") / f"{name}.o", name, addr, rb)
lt = [toks(M.disasm(w, addr + i*4, None)) for i, w in enumerate(t.words)]
lo = [toks(M.disasm(w, addr + i*4, None)) for i, w in enumerate(o.words)]
sm = difflib.SequenceMatcher(a=lt, b=lo, autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == "equal":
        continue
    print(f"{tag:8s} game[{i1}:{i2}] yours[{j1}:{j2}]")
    for k in range(i1, i2):
        print(f"   -{k:3d} {lt[k]}")
    for k in range(j1, j2):
        print(f"   +{k:3d} {lo[k]}")
