#include "common.h"

extern u8 D_800B2428[];
extern u8 D_800B2C7C[];

s32 func_80055D58(void);

s32 func_80057B94(u32 idx, u32 mask, s32 op) {
    u8 *t;
    u32 a;
    u32 b;
    s32 r;

    if (func_80055D58() != 4) {
        u8 *base = D_800B2428;
        u8 *p = base + idx * 112;
        u8 *row = D_800B2C7C + p[0x69] * 48;

        t = row;
        if (*(u16 *) (t + 0xE) & 1) {
            t = 0;
        }
    } else {
        t = D_800B2C7C;
    }
    if (t != 0) {
        a = *(u32 *) (t + 4);
        b = *(u32 *) (t + 8);
        switch ((u32) op) {
        case 0:
            return ((a & b) & mask) == mask;
        case 1:
            return ((a & b) & mask) != 0;
        case 2:
            return (a & mask) == mask;
        case 3:
            return ((~a & b) & mask) != 0;
        default:
            return 0;
        }
    }
    return 0;
}
