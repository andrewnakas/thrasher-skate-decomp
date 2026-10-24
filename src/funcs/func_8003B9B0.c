#include "common.h"

extern u8 D_8008A758;
extern s32 D_8008A70C;
extern s32 D_8008B21C;
extern s32 D_8008A754;
extern s32 D_8008A750;
extern s32 D_8008B218;
extern s32 D_8008A6EC;

void func_8003B9B0(s32 v, s32 arg) {
    if (D_8008A758 != 0) {
        D_8008A758 = 0;
    }
    if (v != 0) {
        D_8008B21C = arg;
        D_8008A754 = 0;
        if (D_8008A70C == 0) {
            D_8008A750 = 1;
            D_8008B218 = D_8008A6EC;
        }
    }
    D_8008A70C = v;
}
