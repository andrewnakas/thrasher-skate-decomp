#include "common.h"

extern u8 D_8008A800[];
extern u32 **D_8008A8EC;
extern u8 D_800828B4[];
extern s32 D_8008A8F4;

void func_8004966C(u16 *, u16 *, u16 *, u32, u32);

typedef struct {
    s32 f0;
    u16 f4;
    u16 f6;
} Rec;

s32 func_80049530(void) {
    u16 b[6];
    u32 **pp;
    u32 *q;
    u16 *p;
    s32 i;
    s32 j;

    pp = D_8008A8EC;
    for (i = 0; i < *(s32 *) D_8008A800; i++) {
        q = *pp;
        for (j = 0x1F; j >= 0; j--) {
            *q = -1;
            q++;
        }
        pp++;
    }

    D_8008A8F4 = 0;
    p = (u16 *) ((u8 *) D_800828B4 + 6);
    for (i = 0; i < *(s32 *) D_8008A800; i++) {
        if (p[-1] < 0x100) {
            b[0] = i;
            b[1] = p[-1];
            b[2] = 0;
            func_8004966C(&b[0], &b[1], &b[2], (0x100 - p[-1]) & 0xFFFF, 0x100);
        }
        if (p[0] < 0x100) {
            b[3] = i;
            b[4] = p[0];
            b[5] = 0;
            func_8004966C(&b[3], &b[4], &b[5], 0x100, (0x100 - p[0]) & 0xFFFF);
        }
        p += 4;
    }

    D_8008A8F4 = 1;
    return 1;
}
