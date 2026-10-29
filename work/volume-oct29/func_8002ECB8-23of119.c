#include "common.h"

void *memset(void *, s32, u32);
u32 func_8002EE94(u8 *, u32 *, u8 *, s32);
s32 func_8002F4C0(s16, s16, u8 *);
s32 func_8002C490(u8 *);
u32 func_8002F054(u8 *, u8 *, u8 *);

s32 func_8002ECB8(u8 *a0, u8 *a1, u8 *a2, s32 a3) {
    u32 t;
    u8 *p;
    s32 r;
    s32 e;
    s32 i;

    e = 0x27100000;
    t = 0;
    if (a1 != 0) {
        memset(a1, 0, 0x30);
    }
    p = (u8 *) func_8002EE94(a0, &t, a2, a3);
    if (p != 0) {
        if ((*(u16 *) p & 0x20) != 0) {
            p = 0;
        }
    }
    if (p != 0) {
        e = func_8002F4C0(*(s16 *) (a0 + 2), *(s16 *) (a0 + 0xA), p + 4);
        if (a2 != 0) {
            *(u32 *) (a2 + 0x0) = 2;
            *(u32 *) (a2 + 0x8) = (u32) (p + 4);
            *(u32 *) (a2 + 0x10) = (u32) p;
            *(u32 *) (a2 + 0x4) = t;
            *(u32 *) (a2 + 0x18) = func_8002C490(p);
            *(u32 *) (a2 + 0xC) = *(u16 *) (*(u32 *) (t + 0x2C) + 2);
            *(u32 *) (a2 + 0x1C) = e;
            *(u32 *) (a2 + 0x14) = *(u32 *) (t + 0x2C);
        }
    }
    if (t == 0) {
        return e;
    }
    r = (s32) t;
    p = *(u8 **) (t + 8);
    if (p != 0) {
        do {
            r = func_8002F054(p, a0, a2);
            if (r != 0x27100000) {
                break;
            }
            p = *(u8 **) (p + 0x40);
        } while (p != 0);
    }
    if (r == 0x27100000) {
        s32 k = 0x27100000;

        for (i = 3; i != -1; i--) {
            p = *(u8 **) (t + 0x34 + i * 4);
            if (p != 0) {
                r = func_8002F054(p, a0, a2);
                if (r != k) {
                    break;
                }
            }
        }
        if (r == 0x27100000) {
            return e;
        }
    }
    if (a2 != 0) {
        *(u32 *) (a2 + 0x2C) = (u32) r;
        *(u32 *) (a2 + 0x4) = t;
    }
    return r;
}
