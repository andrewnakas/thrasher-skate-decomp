#include "common.h"

extern u8 *D_8008AE5C;

s32 func_8001C3CC(u32 i) {
    return *(u16 *) (D_8008AE5C + i * 0x10 + 0xA) -
           *(u16 *) (D_8008AE5C + i * 0x10 + 8) + 1;
}
