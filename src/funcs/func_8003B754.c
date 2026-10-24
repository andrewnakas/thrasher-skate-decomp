#include "common.h"

extern s32 D_8008B23C;
extern s32 D_8008B234;
extern s32 D_8008A6D8;

void func_8003B754(s32 *a0, s32 *a1) {
    if (a0) {
        *a0 = D_8008B23C - D_8008A6D8;
    }
    if (a1) {
        *a1 = D_8008B234 - D_8008A6D8;
    }
}
