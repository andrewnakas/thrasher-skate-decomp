#include "common.h"

extern s16 D_8008B300;
extern s32 D_8008B304;

void func_8003C768(s16 a0, u16 a1) {
    D_8008B300 = a0;
    D_8008B304 = a1;
}
