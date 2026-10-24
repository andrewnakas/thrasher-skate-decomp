#include "common.h"

extern s32 D_8008A9C8;
extern s8 D_8008A9D4[];
extern u8 D_800108B0[];

s32 func_80051574(u8 *a0, s32 *out) {
    if (!D_8008A9C8) {
        printf(D_800108B0, D_8008A9D4, 0x3A9);
        exit(1);
    }

    switch (a0[2]) {
    case 0:
    case 1:
    case 8:
        *out = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        *out = 2;
        break;
    case 7:
        *out = 3;
        break;
    }

    return 0;
}
