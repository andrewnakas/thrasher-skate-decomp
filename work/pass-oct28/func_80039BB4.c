#include "common.h"

extern u8 D_8008B3AC[0x40];
extern u8 *D_8008B1A0;

void func_80039BB4(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 *p;
    u16 v[4];
    u32 t;
    u32 *q;

    p = *(u8 **) D_8008B3AC;
    if (p == 0) {
        return;
    }

    if ((u32) a0 >= 0x200) {
        if ((u32) a0 > 0x200) {
            a0 = 0x200;
        }
    } else if (a0 <= 0) {
        a0 = 0;
    }
    if ((u32) a2 >= 0x200) {
        if ((u32) a2 > 0x200) {
            a2 = 0x200;
        }
    } else if (a2 <= 0) {
        a2 = 0;
    }
    if ((u32) a1 >= 0x1E0) {
        if ((u32) a1 > 0x1E0) {
            a1 = 0x1E0;
        }
    } else if (a1 <= 0) {
        a1 = 0;
    }
    if ((u32) a3 >= 0x1E0) {
        if ((u32) a3 > 0x1E0) {
            a3 = 0x1E0;
        }
    } else if (a3 <= 0) {
        a3 = 0;
    }

    v[1] = *(u16 *) (p + 0) + a0;
    v[2] = a2 - a0;
    v[3] = a3 - a1;
    v[0] = *(u16 *) (p + 2) + a1;
    func_8005A794(p, v, a2);

    t = *(u32 *) p & 0xFFFFFF;
    q = (u32 *) D_8008B1A0;
    *(u32 *) p = (*(u32 *) p & 0xFF000000) | (q[0] & 0xFFFFFF);
    D_8008B1A0 = (u8 *) (q - 1);
    *(u32 *) q = (q[0] & 0xFF000000) | t;
    *(u8 **) D_8008B3AC = p + 0xC;
}
