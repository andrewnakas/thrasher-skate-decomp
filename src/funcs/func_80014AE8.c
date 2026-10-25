#include "common.h"

s32 func_80032C28(s32, s32);
s32 func_80032CF4(s32);
s16 func_80032DCC(s32, s32);

void func_80014AE8(u8 *arg0, s32 *arg1) {
    s16 v[3];
    s32 s;

    s = func_80032C28(arg1[0], arg1[0]);
    s = s + func_80032C28(arg1[1], arg1[1]);
    s = func_80032CF4(s);
    if (s >= 0x42) {
        v[0] = func_80032DCC(arg1[5], arg1[8]);
        v[1] = func_80032DCC(-arg1[2], s);
        v[2] = func_80032DCC(arg1[1], arg1[0]);
    } else {
        v[0] = func_80032DCC(-arg1[7], arg1[4]);
        v[1] = func_80032DCC(-arg1[2], s);
        v[2] = 0;
    }
    *(s16 *)(arg0 + 0x1A) = v[0];
    *(s16 *)(arg0 + 0x1C) = v[1];
    *(s16 *)(arg0 + 0x1E) = v[2];
    *(s16 *)(arg0 + 0x18) = func_80032DCC(-arg1[2], arg1[0]);
}
