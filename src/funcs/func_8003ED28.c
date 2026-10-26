/* cflags: -mno-split-addresses */
#include "common.h"

extern s32 D_8008A6E8[];
extern s32 D_8008A788[2];
extern s32 D_8008A790[2];
extern s32 D_8008B33C[2];
extern s32 D_8008B3AC[];
extern s32 func_80034CF0(s32);

s32 func_8003ED28(void) {
    s32 base = 0;
    s32 off = 0;
    s32 stride = 0;
    s32 count = 0;
    s32 *t788;
    s32 *t790;
    s32 *t33c;
    s32 i;
    s32 r;

    if (D_8008A6E8[0] != 1) {
        if (D_8008A6E8[0] == 0) {
            base = 0x16800;
            off = 0;
            stride = 0x1800;
            count = 2;
        }
    } else {
        base = 0x4000;
        off = 0;
        stride = 0x1800;
        count = 2;
    }
    t788 = D_8008A788;
    t790 = D_8008A790;
    t33c = D_8008B33C;
    for (i = 0; i < count; i++) {
        r = func_80034CF0(base + off);
        t788[i] = r;
        t33c[i] = r + base;
        t790[i] = func_80034CF0(stride);
    }
    D_8008B3AC[0] = 0;
    return 1;
}
