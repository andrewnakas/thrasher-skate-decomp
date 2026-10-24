#include "common.h"

extern u8 D_8008A7A0[8];

void func_8004126C(s32 a0, u8 *a1, u8 *a2) {
    s32 i;
    s32 j;
    s32 found;
    s32 n;
    u32 t1;

    i = D_8008A7A0[a1[3]] - 1;

    for (; i >= 0; i--) {
        t1 = *(u32 *) (a1 + i * 4 + 0x10);
        found = 0;
        if (*(u8 *) (t1 + 6) == 0) {
            continue;
        }

        if (a2 != 0) {
            n = *(u16 *) (a2 + 2);
            a2 = *(u8 **) (a2 + 0x28);
            if (n > 0) {
                for (;;) {
                    j = D_8008A7A0[a2[3]] - 1;
                    if (j >= 0 && found == 0) {
                        for (;;) {
                            if (t1 == *(u32 *) (a2 + j * 4 + 0x10)) {
                                found = 1;
                            }
                            if (--j < 0) {
                                break;
                            }
                            if (found != 0) {
                                break;
                            }
                        }
                    }
                    n--;
                    a2 += a2[2];
                    if (n <= 0) {
                        break;
                    }
                    if (found != 0) {
                        break;
                    }
                }
            }
        }

        if (found != 0) {
            *(u16 *) a1 |= 0x100;
        } else {
            *(u16 *) a1 |= 0x200;
        }
        return;
    }
}
