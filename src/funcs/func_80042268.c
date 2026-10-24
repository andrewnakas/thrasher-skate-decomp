#include "common.h"

void func_80042268(u8 *a0, u16 a1) {
    u8 *p = *(u8 **) (a0 + 0x14);
    s32 n = *(u16 *) (a0 + 8);
    s16 w;

    while (n > 0) {
        if (p[3] == 2) {
            w = *(u16 *) (p + 0x26);
        } else if (p[3] == 3) {
            w = *(u16 *) (p + 0x28);
        } else if (p[3] == 6) {
            w = *(u16 *) (p + 0x26);
        } else if (p[3] == 7) {
            w = *(u16 *) (p + 0x28);
        } else {
            w = -1;
        }
        if (w == a1) {
            *(u16 *) p |= 0x80;
        }
        n--;
        p += p[2];
    }
}
