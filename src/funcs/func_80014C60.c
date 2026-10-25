#include "common.h"

s32 func_80032C28(s32, s32);

void func_80014C60(s16 *arg0, s16 *arg1, s16 *arg2, s32 arg3, u8 arg4) {
    s32 inv;

    inv = 0x10000 - arg3;
    do {
        arg2[0] = (func_80032C28(arg0[0] << 16, arg3) + func_80032C28(arg1[0] << 16, inv)) >> 16;
        arg2[1] = (func_80032C28(arg0[1] << 16, arg3) + func_80032C28(arg1[1] << 16, inv)) >> 16;
        arg2[2] = (func_80032C28(arg0[2] << 16, arg3) + func_80032C28(arg1[2] << 16, inv)) >> 16;
        arg0 += 3;
        arg1 += 3;
        arg2 += 3;
    } while (--arg4 != 0);
}
