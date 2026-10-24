#include "common.h"

extern s32 D_8008A608;
extern s32 D_8008A60C;
extern s32 D_8008B138;
extern s32 D_8008B13C;

void func_80037A5C(s32 a0, u32 a1) {
    a1 = (a1 >> 11) << 11;
    D_8008A608 = a0;
    D_8008A60C = a1;
    D_8008B138 = -1;
    D_8008B13C = -1;
}
