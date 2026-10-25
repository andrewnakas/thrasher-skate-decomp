#include "common.h"

void func_8001D304(u8 *src, u8 *dst) {
    s32 n;

    n = 0;
    if (*src != 0xFF) {
        do {
            *(u8 *) (dst + n + 4) = *src;
            src++;
            n++;
        } while (*src != 0xFF);
    }
    *(u16 *) dst = n;
}
