for v in m17 m18 m19 m20 m21; do
  cp work/v162/$v.c src/funcs/func_800162FC.c
  echo "$v | $(.venv/bin/python tools/match.py func_800162FC 2>&1 | tail -1)"
  .venv/bin/python tools/match.py func_800162FC --show 2>&1 | grep '^!!' | head -12
done
