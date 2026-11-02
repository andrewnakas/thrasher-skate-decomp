#include "common.h"

u32 func_800382C0(u32 a) {
    u32 v;

    v = (a + 4) >> 7;
    /* `a - -v` keeps the game's addu a0,v0 operand order; `a + v` swaps them */
    v = a - -v;
    v += 0x205;
    if (v <= 0x1E000) {
        return v;
    }
    return -1;
}
