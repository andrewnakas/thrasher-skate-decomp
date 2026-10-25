#include "common.h"

extern u8 D_80092614[];

u32 func_800164AC(u32 a0) {
    u16 *e;
    u32 m;
    u8 *b;
    u32 lo;
    u16 h;

    m = a0 & 0xF000;
    b = (u8 *)D_80092614;
    e = *(u16 **)(b + (m >> 10));
    lo = a0 & 0xFFFF;
    if (e == 0) {
        goto fail;
    }
    h = e[2];
    if (lo < h) {
        goto fail;
    }
    if ((s32)lo >= (s32)e[2] + (s32)e[3]) {
        goto fail;
    }
    return (u32)e + *(u16 *)((u32)e + ((lo - e[2]) << 1) + 8);
fail:
    return 0;
}
