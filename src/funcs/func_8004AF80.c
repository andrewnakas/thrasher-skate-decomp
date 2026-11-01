#include "common.h"

extern s32 D_8008A938;
extern u8 *D_800AEA24[];
extern u8 D_800AEAA4[][0x48];
extern s32 D_8008B3FC;
extern s8 D_8008A93C[];
extern u8 D_80010670[];

void func_8004BD20(u8 *);

s32 func_8004AF80(u8 a0) {
    u8 *child;
    u8 *p;

    D_8008A938++;
    if (a0 >= 0x20) {
        printf(D_80010670, D_8008A93C, 0x13F);
        exit(1);
    }
    p = D_800AEA24[a0];
    if (p == 0) {
        printf(D_80010670, D_8008A93C, 0x141);
        exit(1);
    }
    child = *(u8 **) (p + 0x38);
    while (child != 0) {
        func_8004BD20(child);
        child = *(u8 **) (child + 0x10);
    }
    {
        u8 (*tbl)[0x48] = D_800AEAA4;
        *(u16 *) tbl[a0] = 0;
    }
    D_8008B3FC = a0;
    D_800AEA24[a0] = 0;
    D_8008A938--;
    return 0;
}
