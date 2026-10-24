#include "common.h"

extern s32 func_800498FC(u8 a0, u8 a1, s32 a2, u16 a3, u16 a4);

s32 func_8003A3C4(u32 a0, u16 a1, u16 a2) {
    return func_800498FC((a0 >> 8) & 0xFF, (a0 >> 16) & 0xFF, a0 >> 24, a1, a2);
}
