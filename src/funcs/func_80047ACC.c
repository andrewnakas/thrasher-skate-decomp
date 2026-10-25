#include "common.h"

s32 func_80047ACC(s32 *state, u8 *dst) {
    s32 off;
    s32 i;
    s32 j;
    u8 *p;

    off = *state;
    i = 0;
    j = i;
    off++;
    for (; i < 0x400; i += 4, j += 3) {
        p = (u8 *) (off + j);
        dst[i + 0] = p[0];
        dst[i + 1] = p[1];
        dst[i + 2] = p[2];
        dst[i + 3] = 0xFF;
    }
    off += 0x300;
    *state = off;
    return 1;
}
