#include "common.h"

extern u8 D_800A4F00[];

void func_8002AC14(u8 *obj, u32 col) {
    s32 i;
    s32 k;
    s32 r;
    s32 g;
    s32 b;
    s32 d;
    u32 w;
    u8 *p;
    u8 *src;
    u8 *v;
    u8 *dst;
    u8 *t;

    i = obj[5] - 1;
    if (i < 0) {
        return;
    }

    r = col & 0xFF;
    g = (col >> 8) & 0xFF;
    b = (col >> 16) & 0xFF;
    p = (u8 *) ((u32) (i * 4) + (u32) obj);

    do {
        src = *(u8 **) (p + 0x10);
        t = *(u8 **) (src + 4);
        k = src[1];
        v = (u8 *) (*(u32 *) (D_800A4F00 + 4) + 156 * src[0]);
        if (k > 0) {
            do {
                dst = (u8 *) (*(u32 *) (v + 0x48) + 12 * t[4]);
                w = (u32) t[5] << 9;

                d = ((r - 0x80) * (s32) w) >> 16;
                d += t[0];
                if (d > 0xFF) {
                    d = 0xFF;
                }
                if (d < 0) {
                    d = 0;
                }
                dst[8] = d;

                d = ((g - 0x80) * (s32) w) >> 16;
                d += t[1];
                if (d > 0xFF) {
                    d = 0xFF;
                }
                if (d < 0) {
                    d = 0;
                }
                dst[9] = d;

                d = ((b - 0x80) * (s32) w) >> 16;
                d += t[2];
                if (d > 0xFF) {
                    d = 0xFF;
                }
                if (d < 0) {
                    d = 0;
                }
                dst[10] = d;

                t += 8;
                k--;
            } while (k > 0);
        }
        p -= 4;
        i--;
    } while (i >= 0);
}
