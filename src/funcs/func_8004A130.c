#include "common.h"

s32 func_8004A300(s32, s32);
s32 func_8002EE94(s32, s32 *, s32, s32);

typedef union {
    u32 w;
    struct {
        u32 r : 8;
        u32 g : 8;
        u32 b : 8;
        u32 x : 8;
    } c;
} Col_8004A130;

s32 func_8004A130(s32 a0, s32 *a1, s32 *a2) {
    u32 m;
    s32 t;
    s32 r;
    Col_8004A130 v;

    t = 0;
    r = 0;
    if (a1 != 0) {
        t = *a1;
    }
    if (a2 != 0) {
        r = *a2;
    }
    r = func_8002EE94(a0, &t, t, r);
    if (r != 0) {
        v.w = func_8004A300(r, a0);
    } else {
        v.w = 0x808080;
    }
    v.c.r = ((s8) (v.c.r + 0x80) >> 1) - 0x80;
    v.c.g = ((s8) (v.c.g + 0x80) >> 1) - 0x80;
    v.c.b = ((s8) (v.c.b + 0x80) >> 1) - 0x80;
    if (a1 != 0) {
        *a1 = t;
    }
    if (a2 != 0) {
        *a2 = r;
        m = 0xFFFFFF;
    } else {
        m = 0xFFFFFF;
    }
    return m & v.w;
}
