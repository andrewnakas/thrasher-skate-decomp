#include "common.h"

extern u8 *D_8008A560;
extern u8 *D_8008B0F4;
extern u8 *D_8008B0F8;

s32 func_80034C8C(u8 *p, u32 size) {
    u8 *cur = D_8008B0F8;
    u8 *end = cur + size;
    u32 off;
    u8 *q;

    if (cur != p) {
        return 1;
    }
    if (size == 0) {
        D_8008A560 = cur;
        D_8008B0F8 = 0;
        return 0;
    }
    off = (u32) end & 3;
    if (off) {
        q = end - (off - 4);
    } else {
        q = end;
    }
    if (q < D_8008B0F4) {
        D_8008A560 = q;
        return 0;
    }
    return 1;
}
