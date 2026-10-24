#include "common.h"

extern s32 D_8008B23C;
extern s32 D_8008B234;
extern s32 D_8008A6D8;

void func_8003B754(s32 *px, s32 *py) {
    if (px != 0) {
        *px = D_8008B23C - D_8008A6D8;
    }
    if (py != 0) {
        *py = D_8008B234 - D_8008A6D8;
    }
}
