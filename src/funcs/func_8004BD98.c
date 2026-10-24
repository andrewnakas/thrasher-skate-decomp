#include "common.h"

s32 func_8004FD98(u16, u8);

s32 func_8004BD98(u8 *p, u8 idx, s32 *out, u16 *outv) {
    u8 *e;
    u8 c;
    s32 h;
    s8 s;

    *out = 0;
    if (idx < p[0]) {
        return 0;
    }
    if (idx >= p[0] + p[1]) {
        return 0;
    }
    e = p + (idx - p[0]) * 2;
    c = e[4];
    if (c == 0xFF) {
        return 0;
    }
    h = func_8004FD98(*(u16 *) (p + 2), c);
    *out = h;
    s = e[5];
    *outv = s * 100;
    return 1;
}
