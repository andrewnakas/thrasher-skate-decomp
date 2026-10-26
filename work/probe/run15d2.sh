for v in v2 v3 v5 v6; do
  cp work/v15d/$v.c src/funcs/func_80015D38.c
  echo "$v | $(.venv/bin/python tools/match.py func_80015D38 2>&1 | tail -1)"
  .venv/bin/python tools/match.py func_80015D38 --show 2>&1 | grep '^!!' | head -4
done
