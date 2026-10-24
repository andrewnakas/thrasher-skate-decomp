#include "common.h"

extern s32 D_8008A960;
extern u8 D_8008A934[];
extern s32 D_8008A968;
extern s32 D_8008B42C;
extern s32 D_8008B430;
extern s32 D_8008B434;
extern s32 D_8008B438;
extern char D_80010820[];
extern char D_8008A96C[];
extern u8 D_800AFA64[];

s32 func_8004D0E0(u32 x, u32 y) {
    u8 *p;
    u32 i;

    if (D_8008A960 != 0) {
        printf(D_80010820, D_8008A96C, 0x50);
        exit(1);
    }
    i = 0;
    p = D_800AFA64;
    do {
        *(u16 *) p = 0;
        i++;
        p += 0x24;
    } while (i < 0x10);
    D_8008B42C = x;
    D_8008B434 = 0x8000 / x;
    D_8008A968 = y * *(u32 *) D_8008A934 / 1000;
    D_8008B430 = x * x;
    D_8008B438 = 0;
    D_8008A960 = 1;
    return 0;
}
