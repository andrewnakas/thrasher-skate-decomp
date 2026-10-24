#include "common.h"

s32 func_80038610(s32);

void func_80037CB4(u8 *s, u16 *d) {
    u8 c;

    do {
        c = *s;
        *d = func_80038610(c != 0 ? c : 0x20);
        c = *s;
        s++;
        d++;
    } while (c != 0);
}
