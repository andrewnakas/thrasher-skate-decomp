#include "common.h"

s32 func_80019518(s32);
void func_80038A80(s32, s32, s32, s32);
void func_8001954C(s32);
void func_80017C24(s32);

void func_800178BC(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 a = func_80019518(arg0);
    s32 b = func_80019518(arg1);

    func_80038A80(a, b, arg2, arg3);
    func_8001954C(arg1);
    func_8001954C(arg0);
    func_80017C24(arg0);
}
