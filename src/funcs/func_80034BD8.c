#include "common.h"

extern u32 D_8008A560;
extern s32 D_8008B0F8;

void func_80034BD8(u32 a) {
    u32 m;
    u32 t;

    if (a < D_8008A560) {
        m = a & 3;
        if (m != 0) {
            t = m - 4;
            D_8008A560 = a - t;
        } else {
            D_8008A560 = a;
        }
    }
    D_8008B0F8 = 0;
}
