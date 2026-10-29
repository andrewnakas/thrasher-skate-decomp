#include "common.h"

s32 func_800382C0(u32 a0) {
    u32 t;

    t = (a0 + 4) >> 7;
    t = a0 + t;
    t = t + 0x205;
    if (t <= 0x1E000) {
        return t;
    }
    return -1;
}
