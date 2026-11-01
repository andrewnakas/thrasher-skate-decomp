#include "common.h"

s32 func_8004DA90(s32 a0, u8 *a1, u8 *a2);

s32 func_80032400(s32 arg0, u8 arg1, u8 *arg2, u8 *arg3) {
    s32 ret;

    if (arg0 != 0) {
        ret = func_8004DA90(arg0, arg2, arg3);
        *arg2 = (u32) (*arg2 * arg1) >> 7;
    } else {
        ret = 1;
        *arg2 = arg1;
        *arg3 = 0;
    }
    return ret;
}
