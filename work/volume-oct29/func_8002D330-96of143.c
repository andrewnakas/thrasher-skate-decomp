#include "common.h"

s32 func_8002D330(u8 *a0, s32 a1, s32 a2, s32 a3) {
    s32 p0;
    s32 p1;
    s32 p2;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 e0;
    s32 e1;
    s32 n;
    s32 c;
    s32 t;
    s32 k;
    s32 j;
    s32 cross;
    s32 sign;
    u8 *cur;
    u8 *prev;

    p0 = a1 >> 16;
    p1 = a2 >> 16;
    p2 = a3 >> 16;
    n = *(s32 *) (a0 + 4);
    c = *(s32 *) (a0 + 8);
    if (n < 0) {
        n = -n;
    }
    if (c < 0) {
        c = -c;
    }
    if (n < c) {
        t = *(s32 *) (a0 + 0xC);
        if (t < 0) {
            t = -t;
        }
        k = (c < t) ? 2 : 1;
    } else {
        t = *(s32 *) (a0 + 0xC);
        if (t < 0) {
            t = -t;
        }
        k = (n < t) << 1;
    }
    sign = *(s32 *) (a0 + k * 4 + 4);
    j = 2;
    if ((*(u16 *) a0 & 1) != 0) {
        j = 3;
    }
    prev = *(u8 **) (a0 + 0x1C);
    for (; j >= 0; j--) {
        cur = *(u8 **) (a0 + j * 4 + 0x1C);
        if (k == 0) {
            dx = *(s16 *) (prev + 2) - *(s16 *) (cur + 2);
            dz = *(s16 *) (prev + 4) - *(s16 *) (cur + 4);
            e0 = p1 - *(s16 *) (cur + 2);
            e1 = p2 - *(s16 *) (cur + 4);
            cross = dz * e0 - dx * e1;
        } else if (k == 1) {
            dx = *(s16 *) (prev + 0) - *(s16 *) (cur + 0);
            dz = *(s16 *) (prev + 4) - *(s16 *) (cur + 4);
            e0 = p0 - *(s16 *) (cur + 0);
            e1 = p2 - *(s16 *) (cur + 4);
            cross = dx * e1 - dz * e0;
        } else {
            dx = *(s16 *) (prev + 0) - *(s16 *) (cur + 0);
            dy = *(s16 *) (prev + 2) - *(s16 *) (cur + 2);
            e0 = p0 - *(s16 *) (cur + 0);
            e1 = p1 - *(s16 *) (cur + 2);
            cross = dy * e0 - dx * e1;
        }
        if (cross == 0) {
            prev = cur;
            continue;
        }
        if ((cross ^ sign) < 0) {
            return 0;
        }
    }
    return 1;
}
