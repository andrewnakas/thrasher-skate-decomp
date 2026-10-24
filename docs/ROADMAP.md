# Roadmap

1. **Now: matching decomp of SLUS_009.35.** Function by function, gated byte for byte.
2. **Data migration** (maintainers): move `.data`/`.rodata` that belongs to finished source files out of the
   asm into C, file by file, once the functions around it are done. It is a tooling change, re-judged in full.
3. **File boundaries:** regroup `src/funcs/` into the original source files (names survive in strings like
   `zge/zsndSeq.c`) once enough functions are matched to see the boundaries. Generated, not hand-moved.
4. **PLAYMOV.EXE** (the FMV player, 147 KB) is a second, smaller executable: a separate splat config and target
   if anyone wants it.
5. **Native port / recompilation** is a separate product, not a matching aid. A matching decomp of a PS1 game
   ports through a PsyQ compatibility layer (for example PSY-Z) that reimplements libgpu, libgte, libspu and
   libcd. That work starts when the game code is substantially in C; until then a recomp would not help matching.
