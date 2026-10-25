#include "common.h"

extern u8 D_8008A2AD;

s32 func_80020C28(u8 v) {
    D_8008A2AD = v;
    return 0;
}
