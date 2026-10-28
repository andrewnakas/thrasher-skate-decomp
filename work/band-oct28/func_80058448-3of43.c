#include "common.h"

extern s32 D_8008AC60;
extern s32 D_8008AC64;
extern u8 D_8008AE9C[];

extern s32 func_80016470(s32);
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern s32 func_80036BF4(s32, s32);
extern s32 func_80016418(s32, s32);

s32 func_80058448(s32 a0) {
    s32 idx = idx;

    if (D_8008AC64 != 0) {
        func_80016470(D_8008AC60);
        D_8008AC64 = 0;
    }
    if (func_80036A78(*(volatile s32 *) D_8008AE9C, idx, 0) != 0) {
        return 1;
    }
    D_8008AC64 = func_80036B18(*(volatile s32 *) D_8008AE9C);
    if ((u32) (D_8008AC64 - 1) >= 0x1FFF) {
        return 1;
    }
    func_80036BF4(*(volatile s32 *) D_8008AE9C, D_8008AC60);
    return func_80016418(D_8008AC60, D_8008AC64) != 0;
}
