#include "common.h"

extern s32 D_8008B2A4;
extern s32 D_8008B2A8;
extern s32 D_8008B2AC;

void func_8003C18C(s32 a0, s32 a1) {
    D_8008B2A4 = 1;
    D_8008B2A8 = a0;
    D_8008B2AC = a1;
}
