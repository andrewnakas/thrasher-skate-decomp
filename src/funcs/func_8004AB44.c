#include "common.h"

extern u32 D_800AEA24[];
extern u8 D_800AEAA4[];
extern u8 D_800AF3A4[];
extern u32 D_8008B3FC;
extern u32 D_8008B400;
extern u32 D_8008B404;

s32 func_8004AB44(void) {
    u32 i;

    for (i = 0; i < 0x20; i++) {
        D_800AEA24[i] = 0;
        *(u16 *) (D_800AEAA4 + i * 0x48) &= 0x7FFF;
    }
    D_8008B3FC = 0;
    for (i = 0; i < 0x40; i++) {
        *(u8 *) (D_800AF3A4 + i * 0x14) = 0;
    }
    D_8008B400 = 0;
    D_8008B404 = 0;
    return 0;
}
