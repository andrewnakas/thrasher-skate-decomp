#include "common.h"

extern s32 D_8008B328;
extern s32 D_8008B32C;
extern s32 D_8008B330;

void func_8003ED04(void) {
    D_8008B330 = D_8008B328;
    D_8008B32C = D_8008B330 + 0x23D0;
}
