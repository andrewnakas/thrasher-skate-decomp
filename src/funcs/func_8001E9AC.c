#include "common.h"

extern u8 D_8006F2C0[];
extern u16 D_8006F2C0_w[];
extern u8 *func_8001D870(u32);
extern void func_800477D0(u32, u32);

void func_8001E9AC(u16 *a0, u32 a1) {
    u8 *e;
    u8 *v;
    s32 n;
    u16 x;
    u16 y;

    e = D_8006F2C0 + a0[1] * 76;
    if ((*(u16 *) (e + 2) & 0x8000) != 0) {
        *a0 = *a0 | 0x200;
    }
    *a0 = *a0 | (a1 & 0x4C);
    if (*(u16 *) (e + 0x16) == 2) {
        v = func_8001D870(a0[1]);
        n = *(u16 *) (v + 0x18);
        y = *(u16 *) (v + 0x1A);
        x = *(u16 *) (v + 0x26);
        while (n > 0) {
            func_800477D0(x, y);
            n--;
        }
    }
}
