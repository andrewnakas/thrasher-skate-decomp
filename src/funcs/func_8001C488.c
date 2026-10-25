#include "common.h"

extern u16 D_8008AE50;
extern u8 *D_8008AE4C;

void func_8001C488(s32 a0, u16 a1, s32 a2, s32 a3) {
    u16 i = D_8008AE50;
    u8 *p;

    D_8008AE50 = i + 1;
    p = D_8008AE4C + i * 0x10;
    *(s32 *) p = a0;
    *(u16 *) (p + 4) = a1;
    *(s32 *) (p + 8) = a2;
    *(s32 *) (p + 0xC) = a3;
}
