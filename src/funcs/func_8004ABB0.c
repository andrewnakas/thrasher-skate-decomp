#include "common.h"

extern u32 D_800AEA24[];

void func_8004AF80(u8);

s32 func_8004ABB0(void) {
    u8 i;

    for (i = 0; i < 0x20; i++) {
        if (D_800AEA24[i] != 0) {
            func_8004AF80(i);
        }
    }
    return 0;
}
