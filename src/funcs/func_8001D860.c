#include "common.h"

extern s32 D_8008AEC8;
extern s32 D_8008AECC;

s32 func_8001D860(s32 a, s32 b) {
    D_8008AEC8 = a;
    D_8008AECC = b;
    return 0;
}
