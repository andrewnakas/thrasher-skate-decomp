#include "common.h"

s32 func_80036A78(s32, s32, u16);
s32 func_80036B18(s32);
s32 func_80034C20(s32);
void func_80036BF4(s32, s32);

s32 func_80036E6C(s32 a0, s32 a1, u16 a2, s32 *a3) {
    s32 x;
    s32 y;

    if (func_80036A78(a0, a1, a2) != 0) {
        return 0;
    }
    x = func_80036B18(a0);
    y = func_80034C20(x);
    if (y == 0) {
        return 0;
    }
    func_80036BF4(a0, y);
    if (a3 != 0) {
        *a3 = x;
    }
    return y;
}
