#include "common.h"

extern s32 D_8008AD90;
extern s32 D_8008AD88;
extern s32 D_8008AD94;

extern s32 func_80015E8C(s32);
extern s32 func_80019518(s32);
extern void func_8001954C(s32);
extern void func_80015F10(s32);

s32 func_80018C64(s32 a0) {
    u8 flag;
    s32 p;
    s32 v;
    u16 s;

    if (!D_8008AD90) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        flag = 0;
    } else {
        flag = 1;
    }
    p = D_8008AD90 + D_8008AD88 * 0x50;
    if (!a0) {
        a0 = *(s32 *)(p + 0x38);
    }
    v = func_80019518(a0);
    if (!v) {
        return 0;
    }
    s = *(u16 *)(v + 2);
    func_8001954C(a0);
    if (flag) {
        return s;
    }
    D_8008AD90 = 0;
    func_80015F10(D_8008AD94);
    return s;
}
