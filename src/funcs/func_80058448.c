#include "common.h"

s32 func_80016418(s32, s32);
void func_80016470(s32, s32);
s32 func_80036A78(s32, s32, s32);
s32 func_80036B18(s32);
void func_80036BF4(s32, s32);
extern s32 D_8008AC60;
extern s32 D_8008AC64;
extern s32 D_8008AEA0[2];
#define D_8008AE9C (D_8008AEA0[-1])

s32 func_80058448(s32 arg0) {
    if (D_8008AC64 != 0) {
        func_80016470(D_8008AC60, D_8008AC64);
        D_8008AC64 = 0;
    }
    if (func_80036A78(D_8008AE9C, arg0 + 0xA029, 0) == 0) {
        D_8008AC64 = func_80036B18(D_8008AE9C);
        if ((u32) (D_8008AC64 - 1) < 0x1FFF) {
            func_80036BF4(D_8008AE9C, D_8008AC60);
            return func_80016418(D_8008AC60, D_8008AC64) != 0;
        }
        return 1;
    }
    return 1;
}
