#include "common.h"

void func_80013EEC(s32);
s32 func_800411E0(s32);
void func_80013FD0(s32, s32, s32);

void func_8001B0FC(s32 arg0, s32 arg1, s32 arg2) {
    s32 r;

    func_80013EEC(arg0);
    r = func_800411E0(arg1);
    func_80013FD0(arg0, r, arg2);
}
