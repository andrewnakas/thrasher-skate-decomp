#include "common.h"

extern u8 *D_8008AE5C;

u16 func_8001C3F0(u32 i, s32 v) {
    return *(u16 *) (D_8008AE5C + i * 0x10 + 8) + v;
}
