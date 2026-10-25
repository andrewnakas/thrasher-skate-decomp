#include "common.h"

void func_8001E9AC(void *, s32);

s32 func_8001FCB0(u8 *arg0, u8 *arg1) {
    u8 *dst;
    s32 v;
    s32 i;

    for (i = 0; i < 4; i++) {
        dst = arg0 + i * 8;
        v = *(s16 *) (arg1 + i * 0xC + 6);
        *(s16 *) (dst + 0x3C) = v;
        v = *(s16 *) (arg1 + i * 0xC + 0xA);
        *(s16 *) (dst + 0x3E) = v;
        v = *(s16 *) (arg1 + i * 0xC + 0xE);
        *(s16 *) (dst + 0x40) = v;
    }
    *(s32 *) (arg0 + 0x24) = *(s32 *) (arg1 + 0x38);
    func_8001E9AC(arg0, 0);
    return 0;
}
