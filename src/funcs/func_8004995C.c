#include "common.h"

extern u32 **D_8008A8EC;

void func_8004995C(u8 page, s32 shift, u16 row, u16 bits, u16 count, s32 clear) {
    u32 mask;
    u32 *p;
    s32 i;
    u16 n;

    if (bits >= 32) {
        mask = -1;
    } else {
        mask = (1 << bits) - 1;
    }
    mask <<= shift;
    p = D_8008A8EC[page];
    p += row;
    n = count;
    if (clear) {
        for (i = 0; i < n; i++) {
            *p++ &= ~mask;
        }
    } else {
        for (i = 0; i < count; i++) {
            *p++ |= mask;
        }
    }
}
