#include "common.h"

extern u32 D_8008A560;
extern u32 D_8008B0F4;
extern u32 D_8008B0F8;

s32 func_80034C8C(u32 blk, s32 n) {
    u32 old;
    u32 p;
    u32 m;
    u32 q;

    old = D_8008B0F8;
    p = old + n;
    if (old != blk) {
        return 1;
    }
    if (n == 0) {
        D_8008A560 = old;
        D_8008B0F8 = 0;
        return 0;
    }
    m = p & 3;
    if (m != 0) {
        m = m - 4;
        q = p - m;
    } else {
        q = p;
    }
    p = q;
    if (p < D_8008B0F4) {
        D_8008A560 = p;
        return 0;
    }
    return 1;
}
