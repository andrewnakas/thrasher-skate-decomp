#include "common.h"

extern u8 *D_800B10EC[];

void func_80051FD4(u8 *);

s32 func_800522D4(u32 a0) {
    u32 i;
    u8 *p;
    u32 bits;

    bits = a0;
    for (i = 0; i < 0x18; i++) {
        if (bits & (1 << i)) {
            p = D_800B10EC[i];
            if (p != 0) {
                if (*(u16 *) p & 0x100) {
                    bits &= ~(1 << *(u32 *) (p + 0x58));
                }
                func_80051FD4(p);
            }
        }
    }
    return 0;
}
