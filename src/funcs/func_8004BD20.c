#include "common.h"

extern char D_80010670[];
extern char D_8008A93C[];
void func_8004E528(u8, s32);
void func_8004E30C(u8);

void func_8004BD20(u8 *o) {
    u8 f;

    f = o[0];
    if (!(f & 1)) {
        printf(D_80010670, D_8008A93C, 0x468);
        exit(1);
    }
    if (!(f & 2)) {
        func_8004E528(o[8], 0);
        func_8004E30C(o[8]);
    }
    o[0] = 0;
}
