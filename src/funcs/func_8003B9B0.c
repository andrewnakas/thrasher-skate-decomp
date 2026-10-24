#include "common.h"

extern u8 D_8008A758;
extern s32 D_8008A70C;
extern s32 D_8008A754;
extern s32 D_8008A750;
extern s32 D_8008A6EC;
extern s32 D_8008B21C;
extern s32 D_8008B218;

void func_8003B9B0(s32 a0, s32 a1) {
    s32 old;

    if (D_8008A758 != 0) {
        D_8008A758 = 0;
    }

    if (a0 != 0) {
        old = D_8008A70C;
        D_8008B21C = a1;
        D_8008A754 = 0;
        if (old == 0) {
            D_8008A750 = 1;
            D_8008B218 = D_8008A6EC;
        }
    }

    D_8008A70C = a0;
}
