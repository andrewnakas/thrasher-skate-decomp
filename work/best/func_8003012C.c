#include "common.h"

extern u8 D_8006F890[];

u8 *func_8002E8C0(u16, u8 *);

void func_8003012C(u8 *self, u8 *delta) {
    u8 *tab;
    u8 *p;
    s16 *h;
    s32 n;
    s32 m;
    s32 i;

    p = (u8 *) func_8002E8C0(*(u16 *) (self + 0), delta);
    tab = *(u8 *) p * 8 + (s32) D_8006F890;
    n = *(s32 *) (tab + 0);
    m = *(s32 *) (tab + 4);

    if (n > 0) {
        p = self;
        for (i = 0; i < n; i++) {
            *(u16 *) (p + 0x44) += *(s16 *) (delta + 2);
            *(u16 *) (p + 0x46) += *(s16 *) (delta + 6);
            *(u16 *) (p + 0x48) += *(s16 *) (delta + 0xA);
            p += 8;
        }
    }

    if (m > 0) {
        i = 0;
        do {
            h = (s16 *) *(u32 *) (self + 0x84 + i * 0x2C + 0x1C);
            *(s32 *) (self + 0x84 + i * 0x2C + 0x10) =
                -(*(s32 *) (self + 0x84 + i * 0x2C + 4) * h[0])
                - (*(s32 *) (self + 0x84 + i * 0x2C + 8) * h[1])
                - (*(s32 *) (self + 0x84 + i * 0x2C + 0xC) * h[2]);
            i++;
        } while (i < m);
    }

    *(u16 *) (self + 0x30) += *(s16 *) (delta + 2);
    *(u16 *) (self + 0x32) += *(s16 *) (delta + 6);
    *(u16 *) (self + 0x34) += *(s16 *) (delta + 0xA);

    n = *(s16 *) (self + 0x28);
    if (n != 0) {
        h = (s16 *) (*(u32 *) (self + 0x24) + 2);
        n--;
        if (n != -1) {
            do {
                h[0] += *(s16 *) (delta + 2);
                h[1] += *(s16 *) (delta + 6);
                h[2] += *(s16 *) (delta + 0xA);
                h[3] += *(s16 *) (delta + 2);
                h[4] += *(s16 *) (delta + 6);
                h[5] += *(s16 *) (delta + 0xA);
                n--;
                h += 0xE;
            } while (n != -1);
        }
    }
}
