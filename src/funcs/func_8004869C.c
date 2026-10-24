#include "common.h"

void func_8004869C(u8 *a0, u16 a1) {
    u8 *s;
    u16 *d;
    s32 i;
    u16 v;

    s = a0;
    d = (u16 *) a0;
    for (i = 0; i < a1; i++) {
        v = ((s[0] >> 3) << 10) | ((s[1] >> 3) << 5) | (s[2] >> 3);
        *d = v;
        if (v == 0) {
            *d = 0x8000;
        }
        if (*d == 0x7C1F) {
            *d = 0;
        } else if (s[3] != 0) {
            *d |= 0x8000;
        }
        d++;
        s += 4;
    }
}
