#include "common.h"

extern s32 D_8008A9F0;

s32 func_800535A8(s32 a0) {
    if (a0) {
        D_8008A9F0++;
    } else {
        D_8008A9F0--;
    }
    return 0;
}
