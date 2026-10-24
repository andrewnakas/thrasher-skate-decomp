/* cflags: -mno-split-addresses */
#include "common.h"

extern s32 D_80089FE4[];
extern s32 D_80089FF4[];
extern s32 func_80057E78();
extern s32 func_80019FCC();
extern s32 func_80036E1C();
extern s32 func_80014058();
extern void func_80016898();
extern void func_80055D64();
extern void func_800568C0();
extern void func_80056C64();

s32 func_80054508(void) {
    if (func_80057E78()) {
        return 1;
    }
    if (func_80019FCC()) {
        return 1;
    }
    if (func_80014058(func_80036E1C(D_80089FE4[0], D_80089FF4[0]))) {
        return 1;
    }

    func_80016898();
    func_80055D64();
    func_800568C0();
    func_80056C64();
    return 0;
}
