#include "common.h"

extern u32 D_8008A560;
extern u32 D_8008B0F4;
extern u32 D_8008B0F8;

u32 func_80034C20(s32 n) {
    u32 old;
    u32 p;
    u32 m;
    u32 q;

    n = (n + 3) & ~3;
    old = D_8008A560;
    p = old + n;
    m = p & 3;
    if (m != 0) {
        m = m - 4;
        q = p - m;
    } else {
        q = p;
    }
    p = q;
    if (p < D_8008B0F4) {
        D_8008B0F8 = D_8008A560;
        D_8008A560 = p;
        return old;
    }
    return 0;
}
