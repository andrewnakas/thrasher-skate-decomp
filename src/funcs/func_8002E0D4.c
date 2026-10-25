#include "common.h"

extern u8 *D_8008B050;
extern u8 D_800A1C50[0x40];
extern s32 func_8002E14C(u32 a);

s32 func_8002E0D4(u32 v) {
    u8 *p = D_8008B050;
    s32 r = 0;

    while (p != 0) {
        if (func_8002E14C(*(u32 *) p) != 0) {
            *(u32 *) D_800A1C50 = v;
            r = 1;
        }
        p = *(u8 **) (p + 8);
    }
    return r;
}
