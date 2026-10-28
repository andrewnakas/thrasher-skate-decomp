#include "common.h"

extern u8 D_800AEAA4[];
extern u8 D_800AEA24[];
extern u32 D_8008B3FC;
extern u32 D_8008A938;
extern u32 D_8008A934;

s32 func_8004FD98(u16, u32);
s32 func_8005011C(u16, u32);

s32 func_8004ADA4(u8 *a0, u32 a1) {
    u8 *base;
    u8 *p;
    u8 *s0;
    u8 *arg;
    unsigned long long wide;
    u32 idx;
    u32 n;
    u32 *slot;

    wide = (unsigned long long) a0;
    arg = (u8 *) (u32) wide;
    base = D_800AEAA4;
    idx = D_8008B3FC;
    p = (u8 *) (idx * 0x48 + (s32) base);
    n = D_8008A938;
    n++;
    D_8008A938 = n;
    s0 = 0;
    for (;;) {
        s0 = p;
        if ((*(u16 *) s0 & 0x8000) == 0) {
            *(u16 *) s0 = 0x8000;
            idx++;
            D_8008B3FC = idx;
            if (idx == 0x20) {
                D_8008B3FC = 0;
            }
            break;
        }
        idx++;
        if (idx == 0x20) {
            p = base;
            idx = 0;
        } else {
            p += 0x48;
        }
        if (idx == D_8008B3FC) {
            break;
        }
    }
    if (s0 == 0) {
        D_8008A938 = n - 1;
        return 0xFF;
    }
    *(u8 *) (s0 + 2) = 0;
    n = D_8008A934;
    *(u32 *) (s0 + 0x30) = 0x3E8000 / n;
    *(u32 *) (s0 + 0x34) = (n << 12) / 1000;
    *(u16 *) s0 = (*(u16 *) s0 | (a1 & 0xFFFC));
    *(u8 *) (s0 + 3) = 0x7F;
    *(u32 *) (s0 + 0x38) = 0;
    n = *(u32 *) (arg + 8) + 4;
    *(u32 *) (s0 + 0x24) = n;
    *(u32 *) (s0 + 0x28) = n;
    *(u8 *) (s0 + 5) = 0x7F;
    *(u8 *) (s0 + 4) = *(u8 *) (arg + 0);
    *(u32 *) (s0 + 8) = (u32) a0;
    *(u8 *) (s0 + 6) = *(u8 *) (arg + 1);
    if (*(u8 *) (arg + 2) != 0xFF) {
        *(u32 *) (s0 + 0x1C) = func_8004FD98(*(u16 *) (s0 + 0x44), *(u8 *) (arg + 2));
    } else {
        *(u32 *) (s0 + 0x1C) = 0;
    }
    if (*(u8 *) (arg + 3) != 0xFF) {
        *(u32 *) (s0 + 0x20) = func_8005011C(*(u16 *) (s0 + 0x44), *(u8 *) (arg + 3));
    } else {
        *(u32 *) (s0 + 0x20) = 0;
    }
    *(u16 *) (s0 + 0x44) = *(u16 *) (arg + 0xE);
    slot = (u32 *) (idx * 4 + (s32) D_800AEA24);
    *slot = (u32) s0;
    n = D_8008A938;
    D_8008A938 = n - 1;
    return idx & 0xFF;
}
