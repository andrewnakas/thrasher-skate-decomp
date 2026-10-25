#include "common.h"

s32 func_80032C28(s32, s32);
s32 func_80032CF4(s32);
s16 func_80032DCC(s32, s32);

void func_80026FBC(s32 *arg0, s16 *arg1) {
    s32 s;

    s = func_80032C28(arg0[0], arg0[0]);
    s = s + func_80032C28(arg0[1], arg0[1]);
    s = func_80032CF4(s);
    if (s >= 7) {
        arg1[0] = func_80032DCC(arg0[5], arg0[8]);
        arg1[1] = func_80032DCC(-arg0[2], s);
        arg1[2] = func_80032DCC(arg0[1], arg0[0]);
    } else {
        arg1[0] = func_80032DCC(-arg0[7], arg0[4]);
        arg1[1] = func_80032DCC(-arg0[2], s);
        arg1[2] = 0;
    }
}
