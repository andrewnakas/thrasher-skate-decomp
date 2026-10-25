#include "common.h"

s32 func_80036A78(void *, s32, u16);
s32 func_80036B18(void *);
s32 func_80034C20(s32);
s32 func_80034CF0(s32);
void func_80036BF4(void *, s32);

s32 func_8001C1DC(void *arg0, s32 arg1, u16 arg2, s32 *arg3, s32 arg4) {
    s32 a;
    s32 b;

    if (func_80036A78(arg0, arg1, arg2) != 0) {
        return 0;
    }
    a = func_80036B18(arg0);
    if (arg4 == 0) {
        b = func_80034C20(a);
    } else {
        b = func_80034CF0(a);
    }
    if (b == 0) {
        return 0;
    }
    func_80036BF4(arg0, b);
    if (arg3 != 0) {
        *arg3 = a;
    }
    return b;
}
