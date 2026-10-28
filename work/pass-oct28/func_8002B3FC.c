#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3;

u32 *func_8002C1B4(V3 v, u32 a1);

void func_8002B3FC(u8 *a0) {
    V3 v;
    u32 *p;
    u32 e;
    s32 flag;

    v.x = *(s16 *) (a0 + 0xA) << 16;
    v.y = *(s16 *) (a0 + 0xC) << 16;
    v.z = *(s16 *) (a0 + 0xE) << 16;

    p = func_8002C1B4(*(V3 *) &v, *(u32 *) (a0 + 0x2C));
    flag = 0;
    e = *(u32 *) (a0 + 0x3C);
    do {
        if (func_8002B674(a0, e)) {
            if (*(u32 *) (a0 + 0x3C) == e) {
                break;
            }
            if (*(u32 *) (a0 + 0x3C) != 0) {
                func_8002B2B0(a0, e);
            } else {
                func_8002B564(a0, e);
            }
        } else if (*(u32 *) (a0 + 0x3C) == e) {
            func_8002B57C(a0, e);
            flag = 1;
        }
    } while ((e = *p++) != 0);

    if (flag != 0) {
        if (*(u32 *) (*(u32 *) (a0 + 0x3C)) & 0x40) {
            if (*(u32 *) (a0 + 0x1C) == 0) {
                func_8002AEF4(a0);
            }
        } else if (*(u32 *) (a0 + 0x1C) != 0) {
            func_8002B060(a0);
        }
    }
}
