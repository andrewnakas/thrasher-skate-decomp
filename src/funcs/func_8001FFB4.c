#include "common.h"

extern u8 D_8006F2C0[];

s32 func_8001D99C(u32);
void func_8001D804(u32, u8 *);

s32 func_8001FFB4(void) {
    u8 *rec;
    u8 *dst;
    u8 *p;
    u32 i;

    i = 0;
    p = D_8006F2C0;
    dst = p + 8;
    rec = p;
    for (; i < 0x12; i++) {
        if ((*(u16 *)(rec + 0x14) & 1) || func_8001D99C(*(u16 *)rec)) {
            func_8001D804(*(u16 *)rec, dst);
        }
        dst += 0x4C;
        rec += 0x4C;
    }
    return 0;
}
