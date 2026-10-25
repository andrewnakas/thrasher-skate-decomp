#include "common.h"

extern u8 *D_8008AE5C;

s32 func_8001C3B4(u32 i) {
    return *(s32 *) (D_8008AE5C + i * 0x10 + 0xC);
}
