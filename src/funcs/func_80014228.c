#include "common.h"

extern s32 D_8008ACEC;
extern s32 D_8008ACF0;

u8 *func_80014228(u8 *arg0) {
    u8 *p;
    s32 c;

    D_8008ACEC = 0;
    D_8008ACF0 = 0;
    c = *(s32 *)(arg0 + 0x10);
    if (c == 0) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0xC);
    *(s32 *)(arg0 + 0x10) = c - 1;
    D_8008ACEC = *(s32 *)(p + 0x0);
    D_8008ACF0 = *(s32 *)(p + 0x4) + *(s32 *)(arg0 + 0x0);
    p = p + 4;
    p = p + (*(u16 *)(*(u8 **)(arg0 + 0x8)) << 3);
    *(u8 **)(arg0 + 0xC) = p;
    return (u8 *)&D_8008ACEC;
}
