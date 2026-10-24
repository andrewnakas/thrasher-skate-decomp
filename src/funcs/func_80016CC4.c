#include "common.h"

extern u16 D_8008AD74;
extern u16 D_8008AD76;
extern u16 D_8008AD78;
extern u16 D_8008AD7A;

void func_80039BB4(s32, s32, s32, s32);

void func_80016CC4(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    D_8008AD74 = arg0;
    D_8008AD76 = arg1;
    D_8008AD78 = arg2;
    D_8008AD7A = arg3;
    func_80039BB4(arg0, arg1, arg2, arg3);
}
