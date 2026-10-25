#include "common.h"

extern s32 D_8008A2BC;
extern s32 D_8008AF64;
extern void func_80024720(void);

void func_8002582C(u8 *self) {
    u32 i;

    func_80024720();
    *(s32 *) (self + 0xFF8) = 6;
    for (i = 0; i < *(u32 *) self; i++) {
        *(s16 *) (self + 4 + i * 0x8C) = 1;
    }
    (&D_8008AF64)[D_8008A2BC] = 0;
}
