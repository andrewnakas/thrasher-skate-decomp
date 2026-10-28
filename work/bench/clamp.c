#include "common.h"

#define CLAMPX(x, hi) ((x) > (hi) ? (hi) : ((x) <= 0 ? 0 : (x)))

s32 clamp2(s32 x, s32 lo, s32 hi);

s32 g;

s32 v1_elseif(s32 a) {
    if (a > 0x200) { a = 0x200; } else if (a <= 0) { a = 0; }
    return a;
}

s32 v2_helper(s32 a) { return clamp2(a, 0, 0x200); }
s32 clamp2(s32 x, s32 lo, s32 hi) {
    if (x > hi) { x = hi; } else if (x < lo) { x = lo; }
    return x;
}

s32 v3_ternary(s32 a) { return (a < 0x200) ? ((a > 0) ? a : 0) : 0x200; }

s32 v4_unsig(s32 a) {
    u32 u;
    s32 r;
    u = (u16) a;
    r = u;
    if (u > 0x200) { r = 0x200; } else if ((s32) u <= 0) { r = 0; }
    return r;
}

s32 v5_result(s32 a) {
    s32 r;
    r = a;
    if (r > 0x200) { r = 0x200; } else if (r <= 0) { r = 0; }
    return r;
}

s32 v6_macro(s32 a) {
    a = CLAMPX(a, 0x200);
    return a;
}

s32 v7_early(s32 a) {
    if (a > 0x200) return 0x200;
    if (a <= 0) return 0;
    return a;
}

s32 v8_bounds(s32 a) {
    s32 hi;
    hi = 0x200;
    if (a > hi) { a = hi; } else if (a <= 0) { a = 0; }
    return a;
}
