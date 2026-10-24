#include "common.h"

void func_80041240(u8 *a0, u8 *a1, s32 a2) {
    u32 n = *(u16 *) (a0 + 6);

    if (n != 0) {
        do {
            a1 += 0x10;
            *(s32 *) (a1 + 4) = a2;
            n--;
            a2 += 6;
        } while (n != 0);
    }
}
