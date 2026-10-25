#include "common.h"

void func_80019EE4(u8 *dst, u8 *src, s32 n) {
    s32 i = n - 1;

    if (n != 0) {
        do {
            *dst++ = *src++;
        } while (--i != -1);
    }
}
