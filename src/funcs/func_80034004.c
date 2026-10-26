#include "common.h"

u16 func_80034004(u8 *dst, u8 *src, u16 n) {
    u8 c;
    u16 i;

    i = 0;
    for (i = 0; i < n; i++) {
        c = *src;
        if (c == 0) {
            goto check;
        }
        *dst = c;
        src++;
        dst++;
    }
    goto check;
count:
    i++;
    src++;
check:
    if (*src != 0) {
        goto count;
    }
    return i;
}
