for v in m1 m2 m3 m4 m5 m6 m7 m8 m9 m10 m11 m12 m13 m14 m15 m16; do
  cp work/v162/$v.c src/funcs/func_800162FC.c
  out=$(.venv/bin/python tools/match.py func_800162FC 2>&1 | tail -1)
  dec=$(.venv/bin/python tools/match.py func_800162FC --show 2>&1 | grep -c 'addiu       \$s1, \$s1, -0x1')
  echo "$v | $out | dec=$dec"
done
