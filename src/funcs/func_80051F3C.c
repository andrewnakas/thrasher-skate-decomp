#include "common.h"

extern u8 D_800B114C[];
extern s32 D_8008B448;
extern void func_80036394(s32);

void func_80051F3C(u8 *a0) {
    u8 *p;
    u32 i;

    func_80036394(*(s32 *) (a0 + 0xC));
    for (i = 0, p = D_800B114C; i < 16; i++, p += 0x10) {
        if (a0 == p) {
            *(s32 *) (p + 4) = 0;
            D_8008B448 = i;
            break;
        }
    }
}
