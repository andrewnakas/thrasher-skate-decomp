#include "common.h"

extern u32 D_8008AC84;

void func_80011B48(void) {
    u32 x;

    x = D_8008AC84;
    x = ((x << 4) | (x >> 28)) + ((x >> 16) | (x << 16));
    x ^= 0x87654321;
    x = (x >> 16) | (x << 16);
    D_8008AC84 = x;
}
