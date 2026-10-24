#include "common.h"

extern s32 D_8008B328;
extern u8 *func_80034C20(s32);

s32 func_8003ECE0(void) {
    D_8008B328 = (s32) func_80034C20(0x2400);
    return 0;
}
