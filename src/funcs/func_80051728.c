#include "common.h"

extern s32 D_8008A9C8;
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

s32 func_80051728(u8 *a0) {
    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x405);
        exit(1);
    }
    *(s32 *) (a0 + 0x38) = 0;
    switch (a0[2]) {
    case 2:
        a0[2] = 1;
        break;
    case 3:
    case 4:
        a0[2] = 5;
        break;
    case 7:
        a0[3] = 0;
        a0[2] = 0;
        break;
    }
    return 0;
}
