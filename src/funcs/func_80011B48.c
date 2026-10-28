#include "common.h"

extern u32 D_8008AC84;

u32 func_80011B48(void) {
    u32 s = D_8008AC84;
    u32 rol = (s << 4) | (s >> 28);
    u32 hi = s >> 16;
    u32 lo = s << 16;
    u32 z = rol + (hi | lo);

    z ^= 0x87654321;
    return D_8008AC84 = (z << 16) | (z >> 16);
}
