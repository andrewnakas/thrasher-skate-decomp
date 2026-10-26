for v in x1 x2 x3 x4 x5; do
  cp work/v15d/$v.c src/funcs/func_80015D38.c
  echo "$v | $(.venv/bin/python tools/match.py func_80015D38 2>&1 | tail -1)"
done
