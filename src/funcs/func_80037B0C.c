#include "common.h"

extern void (*D_8008A654)(s32);
extern s32 D_8008B188;

void func_80037B0C(s32 a0, s32 a1) {
    if (a0 == 1) {
        if (D_8008A654 != 0) {
            D_8008B188 = a1;
            D_8008A654(0);
            D_8008A654 = 0;
        }
    }
}
