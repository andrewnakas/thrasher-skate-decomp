#include "common.h"

extern s32 D_8008B248;
extern s32 D_8008B24C;
extern s32 D_8008B22C;
extern s32 D_8008B230;

void func_8003B854(void) {
    if (D_8008B248 < 0x141) {
        D_8008B22C = 0x10000;
    } else {
        D_8008B22C = 0x19999;
    }
    if (D_8008B24C < 0x101) {
        D_8008B230 = 0x10000;
    } else {
        D_8008B230 = 0xF000;
    }
}

