#include "common.h"

s32 func_800363F8(s32, s32, s32);
s32 func_800367F4(s32);
void func_8003663C(s32, s32, s32);
void func_80036758(s32);

s32 func_8001B1CC(s32 arg0, s32 arg1) {
    s32 r = func_800363F8(arg0, 1, 0);
    s32 t;

    if (r == 0) {
        return 1;
    }
    t = func_800367F4(r);
    func_8003663C(r, arg1, t);
    func_80036758(r);
    return 0;
}
