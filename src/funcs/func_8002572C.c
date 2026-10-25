#include "common.h"

extern s32 D_8008A2BC;
extern s32 D_8008AF5C;
extern void func_80024720(void);

void func_8002572C(u8 *self) {
    u32 i;

    func_80024720();
    *(s32 *) (self + 0xFF8) = 6;
    for (i = 0; i < *(u32 *) self; i++) {
        *(s32 *) (self + 0x40 + i * 0x8C) = 0xB333;
        *(s32 *) (self + 0x44 + i * 0x8C) = 0x10000;
    }
    (&D_8008AF5C)[D_8008A2BC] = 0;
}
