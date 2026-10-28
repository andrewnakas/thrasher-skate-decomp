#include "common.h"

extern u8 D_800A6294[];
extern s32 D_8008B108;

void func_80035BC0(u8 *p, s32 idx) {
    u8 *base = D_800A6294;
    u8 *e = (u8 *) ((u32) idx * 12 + (u32) base);
    u32 a = p[2] & 0xFF;
    u32 b = p[3] & 0xFF;

    e[0] = 4;
    *(u32 *) (e + 4) = ~((a << 8) | b) & 0xFFFF;
    D_8008B108 = D_8008B108 + 1;
}
