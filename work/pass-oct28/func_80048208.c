#include "common.h"

extern u8 D_8008A8B4;

s32 func_80048208(u8 *a0, u8 *a1, u8 *a2) {
    u8 *p;
    s32 n;
    s32 r;
    u8 *q;

    r = 1;
    p = (u8 *) func_800363F8(a0, 1, 0);
    if (p == 0) {
        return r;
    }

    n = func_800367F4(p);
    q = (u8 *) func_80034C20(n);
    if (q == 0) {
        func_80036758(p);
        return 1;
    }

    func_8003663C(p, q, n);
    func_80036758(p);
    n = func_8004813C(q);
    if (n == 0) {
        return 1;
    }

    switch (n) {
    case 1:
        D_8008A8B4 = 0;
        r = func_80047C94(q, a1, a2);
        break;
    case 5:
        D_8008A8B4 = 1;
        r = func_80047C94(q, a1, a2);
        break;
    case 2:
        r = func_80047B28(q, a1, a2);
        break;
    case 3:
        break;
    case 4:
        r = func_80047EF0(q, a1, a2);
        break;
    }

    func_80034BD8(q);
    return r;
}
