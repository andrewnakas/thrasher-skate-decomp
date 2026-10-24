#include "common.h"

extern u16 D_8008B1A4;

u8 *func_80039FF4(u32 *a0, u8 *a1, u16 a2) {
    D_8008B1A4 = a2;
    a1[3] = 1;
    *(u32 *) (a1 + 4) = (a2 & 0x9FF) | 0xE1000200;
    *(u32 *) a1 = (*(u32 *) a1 & 0xFF000000) | (a0[0] & 0xFFFFFF);
    a0[0] = (a0[0] & 0xFF000000) | ((u32) a1 & 0xFFFFFF);
    return a1 + 8;
}
