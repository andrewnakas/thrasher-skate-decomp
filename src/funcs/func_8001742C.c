#include "common.h"

extern s32 D_8008AD88;
extern u8 *D_8008AD90;
extern s32 D_8008AD94;

s32 func_80015E8C(s32);
void func_80015F10(s32);

void func_8001742C(s32 arg0) {
    u8 alloc;
    u8 *e;

    if (arg0 == 0) {
        return;
    }
    if (D_8008AD90 == 0) {
        D_8008AD90 = (u8 *)func_80015E8C(D_8008AD94);
        alloc = 0;
    } else {
        alloc = 1;
    }
    e = D_8008AD90 + D_8008AD88 * 0x50;
    *(s32 *)(e + 0x14) = arg0;
    if (alloc == 0) {
        D_8008AD90 = 0;
        func_80015F10(D_8008AD94);
    }
}
