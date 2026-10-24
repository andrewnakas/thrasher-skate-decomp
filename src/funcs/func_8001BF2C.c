#include "common.h"

extern s32 D_8008A160;
extern s32 D_8008A164;
extern u8 D_80092874[];

s32 func_8001D08C(void);
s32 func_8001D0A0(s32);

void func_8001BF2C(void) {
    s32 i;

    D_8008A164 = func_8001D08C();
    D_8008A160 = 2;
    for (i = 2; i < D_8008A164; i++) {
        ((s32 *)D_80092874)[i - D_8008A160] = func_8001D0A0(i) + 0x3C;
    }
}
