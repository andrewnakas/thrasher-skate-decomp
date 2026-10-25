#include "common.h"

s32 func_80032C28(s32, s32);

void func_80014DA8(s16 *arg0, s16 *arg1, s32 *arg2, u8 arg3) {
    u8 i;

    i = 0;
    do {
        arg2[i] = 0x10000;
        arg0[0] = (func_80032C28(arg0[0] << 16, 0x10000) + func_80032C28(arg1[0] << 16, 0)) >> 16;
        arg0[1] = (func_80032C28(arg0[1] << 16, arg2[i]) + func_80032C28(arg1[1] << 16, 0)) >> 16;
        arg0[2] = (func_80032C28(arg0[2] << 16, arg2[i]) + func_80032C28(arg1[2] << 16, 0)) >> 16;
        arg0 += 3;
        arg1 += 3;
        i++;
    } while (--arg3 != 0);
}
