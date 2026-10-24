/* cflags: -mno-split-addresses */
#include "common.h"

extern s32 D_80089FE4[4];
extern s32 D_8008A01C[4];
extern s32 D_8008A7FC;
extern s32 D_8008B3C0;
s32 func_80036E1C(s32, s32);
s32 func_8003682C();

s32 func_80046530(void) {
    s32 h;

    h = func_80036E1C(D_80089FE4[0], D_8008A01C[0]);
    D_8008A7FC = func_8003682C(h);
    if (D_8008A7FC == 0) {
        return 1;
    }
    D_8008B3C0 = D_8008A7FC;
    return 0;
}
