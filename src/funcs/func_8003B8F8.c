/* cflags: -mno-split-addresses */
#include "common.h"

extern u32 D_80089FE4[];
extern u32 D_8008A050[];
extern s32 D_8008A6F4;
extern s32 D_8008B20C;
extern s32 D_8008B210;
extern s32 D_8008B214;

s32 func_80036E1C(u32, u32);
s32 func_8003682C(s32);
s32 func_80036E6C(s32, s32, s32, s32);
void func_80037DAC(s32, s32);

s32 func_8003B8F8(void) {
    s32 h;

    D_8008A6F4 = func_8003682C(func_80036E1C(D_80089FE4[0], D_8008A050[0]));
    if (D_8008A6F4 == 0) {
        return 1;
    }
    h = func_80036E6C(D_8008A6F4, 0x14, 0, 0);
    D_8008B20C = h;
    func_80037DAC(0, h);
    h = func_80036E6C(D_8008A6F4, 0x15, 0, 0);
    D_8008B210 = h;
    func_80037DAC(1, h);
    h = func_80036E6C(D_8008A6F4, 0x16, 0, 0);
    D_8008B214 = h;
    func_80037DAC(2, h);
    return 0;
}
