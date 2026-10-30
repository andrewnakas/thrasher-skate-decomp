#include "common.h"

extern u32 D_8008B284;
extern u32 D_8008B278;
extern u32 D_8008B29C;
extern u32 D_8008B2A0;
extern u32 D_8008B260;
extern u32 D_8008B268;
extern u32 D_8008B26C;
extern u32 D_8008B270;
extern u16 D_8008B288;
extern u16 D_8008B28A;
extern u16 D_8008B28C;
extern u32 D_8008B27C;
extern u32 D_8008B280;
extern u32 D_8008B25C;
extern u32 D_8008B264;
extern u32 D_8008234C[];

void func_8003BE34(s32);

void func_8003BDB8(void) {
    u32 hi = 0xFFFF0000;
    u32 one = 0x10000;

    D_8008B284 = one;
    D_8008B278 = one;
    D_8008B29C = one;
    D_8008B2A0 = one;
    D_8008B260 = hi;
    D_8008B268 = 0;
    D_8008B26C = 0;
    D_8008B270 = 0;
    D_8008B288 = 0;
    D_8008B28A = 0;
    D_8008B28C = 0;
    D_8008B27C = 0;
    D_8008B280 = 0;
    D_8008B25C = 0;
    D_8008B264 = 0;
    D_8008234C[0x4A] = 0x1000;
    D_8008234C[0x4B] = 0x1000;
    D_8008234C[0x4C] = 0x1000;
    func_8003BE34(0x271C);
}
