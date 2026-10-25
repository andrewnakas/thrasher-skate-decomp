#include "common.h"

extern u8 *D_8008AD90;
extern s32 D_8008AD94;
extern s32 D_8008AD88;

u8 *func_80015E8C(s32);
void func_80015F10(s32);
void func_80038970(u32, s32, s32, s16, s16, s16, s16);

void func_800175FC(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u8 *p;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 t;
    s16 u;
    u8 made;
    s32 f;
    s32 s;

    x0 = arg0;
    y0 = arg1;
    x1 = arg2;
    y1 = arg3;
    if (D_8008AD90 == NULL) {
        made = 0;
        D_8008AD90 = func_80015E8C(D_8008AD94);
    } else {
        made = 1;
    }
    p = D_8008AD90 + D_8008AD88 * 0x50;
    if (x0 > x1) {
        t = x0;
        x0 = x1;
        x1 = t;
        u = y0;
        y0 = y1;
        y1 = u;
    }
    s = *(u16 *)(p + 0x10);
    f = 0;
    if (s & 2) {
        f = 1;
    } else if (s & 4) {
        f = 2;
    } else if (s & 1) {
        f = 3;
    }
    func_80038970(*(u32 *)(p + 0xC), f, *(u8 *)(p + 0x24), x0, y0, x1, y1);
    if (made == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
