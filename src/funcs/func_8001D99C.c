#include "common.h"

extern u8 D_8008AED0[8];

s32 func_8001D99C(u32 i) {
    u32 w;

    w = (i >> 5) << 2;
    return (*(u32 *) (D_8008AED0 + w) & (1 << (i & 0x1F))) != 0;
}
