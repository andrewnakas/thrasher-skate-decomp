#include "common.h"

s32 func_800382C0(u32 x) {
    u32 limit = 0x1E000;
    u32 v = (x + 4) >> 7;

    v += x;
    v += 0x205;
    if (limit < v) {
        v = -1;
    }
    return (s32) v;
}
