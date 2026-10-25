#include "common.h"

extern u16 D_8008AE68;
extern u8 *D_8008AE64;

void func_8001C2B8(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4) {
    u16 i = D_8008AE68;
    u8 *p;

    D_8008AE68 = i + 1;
    p = D_8008AE64 + i * 0x10;
    *(s32 *) p = a0;
    *(u16 *) (p + 4) = a1;
    *(u16 *) (p + 6) = a2;
    *(s32 *) (p + 8) = a3;
    *(s32 *) (p + 0xC) = a4;
}
