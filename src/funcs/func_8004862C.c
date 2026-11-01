#include "common.h"

extern u16 D_800AE794[];

void func_8004862C(s32 arg0, s16 w) {
    s32 x = (arg0 & 0x3F) * 16;
    s32 y = (u16) arg0 >> 6;
    u16 mask = (1 << (w / 16)) - 1;
    s32 bits = mask << ((x - 0x300) / 16);
    s32 row = y - 0x100;

    D_800AE794[row] &= ~bits;
}
