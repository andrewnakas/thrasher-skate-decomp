#include "common.h"

extern s32 D_8008B1FC[2];
extern s32 D_8008B204;

void func_8003AAAC(s32 a0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8008B1FC[i] == a0) {
            D_8008B1FC[i] = 0;
            D_8008B204--;
        }
    }
}
