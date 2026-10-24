/* cflags: -mno-split-addresses */
#include "common.h"
extern u8 D_8008A784[];
extern u8 D_8008A7F0[];
extern u8 D_8008A76C[];
extern u8 D_8008A768[];
extern u8 D_8008A69C[];

void func_80011C40(s32 arg0) {
    if (arg0 & 2) {
        D_8008A784[0] = 0;
    }
    if (arg0 & 1) {
        D_8008A7F0[0] = 0;
    }
    if (arg0 & 4) {
        D_8008A76C[0] = 0;
    }
    if (arg0 & 8) {
        D_8008A768[0] = 0;
    }
    if (arg0 & 0x40) {
        D_8008A69C[0] = 0;
    }
}
