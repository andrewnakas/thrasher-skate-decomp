#!/bin/sh
cd /home/nakas/Documents/Thrasher_Decomp
while read name src; do
  out=$(.venv/bin/python tools/match.py "$name" --src "$src" 2>&1 | head -1)
  echo "$name|$src|$out"
done < work/park-list.txt > work/park-scan.txt
echo DONE >> work/park-scan.txt
