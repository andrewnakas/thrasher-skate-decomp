#include "common.h"

extern u8 D_8006F2C0[];

extern void func_800477D0(u16 a, u16 b);
extern u8 *func_8001D870(u16 idx);

void func_8001E9AC(u8 *p, u32 flags) {
    u16 idx;
    u8 *e;
    u8 *r;
    s32 n;
    u16 a;
    u16 b;

    idx = *(u16 *) (p + 2);
    e = D_8006F2C0 + idx * 0x4C;
    if ((*(u16 *) (e + 2) & 0x8000) != 0) {
        *(u16 *) p |= 0x200;
    }
    *(u16 *) p |= flags & 0x4C;
    if (*(u16 *) (e + 0x16) == 2) {
        r = func_8001D870(*(u16 *) (p + 2));
        n = *(u16 *) (r + 0x18);
        b = *(u16 *) (r + 0x1A);
        a = *(u16 *) (r + 0x26);
        if (n > 0) {
            do {
                func_800477D0(a, b);
            } while (--n > 0);
        }
    }
}
