#include "common.h"

void func_80016E60(s32, s32);

void func_800175C0(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    func_80016E60(arg3, arg0 | (arg1 << 8) | (arg2 << 16));
}
