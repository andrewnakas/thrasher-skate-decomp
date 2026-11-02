/* a4 r5: u16 digit count, while (n++ < width) pad loop, val copied from the param after p = buf. */
#include "common.h"

extern u8 D_800818D4[];

u8 *func_80034698(u8 *buf, u32 arg1, u16 base, u16 width) {
    u8 *p;
    u8 *q;
    u16 n;
    u8 c;
    u32 val;

    p = buf;
    val = arg1;
    n = 0;
    do {
        *p++ = D_800818D4[val % base];
        val /= base;
        n++;
    } while (val != 0);
    while (n++ < width) {
        *p++ = 0x30;
    }
    *p = 0;
    p--;
    for (q = buf; q < p; q++, p--) {
        c = *q;
        *q = *p;
        *p = c;
    }
    return buf;
}
