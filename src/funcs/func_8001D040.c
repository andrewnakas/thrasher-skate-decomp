/* cflags: -mno-split-addresses */
#include "common.h"

extern s32 D_8008AE78;
extern s32 D_80089FE4[16];
s32 func_8001D0A0(void);
s32 func_80036E1C(s32, s32);
s32 func_8003682C(s32);

s32 func_8001D040(void) {
    s32 r;

    r = func_8001D0A0();
    r = func_80036E1C(D_80089FE4[0], r + 0x50);
    r = func_8003682C(r);
    D_8008AE78 = r;
    return (u32) r < 1;
}
