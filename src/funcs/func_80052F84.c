#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_800B134E[16];
extern char D_80010920[];
extern char D_8008AA00[];

s32 func_80052F84(s32 *a0) {
    if (D_8008A9EC == 0) {
        printf(D_80010920, D_8008AA00, 0x242);
        exit(1);
    }

    switch (D_800B134E[0]) {
    case 1:
    case 2:
        *a0 = 1;
        break;
    case 3:
    case 4:
    case 6:
        *a0 = 2;
        break;
    case 5:
        *a0 = 3;
        break;
    }

    return 0;
}
