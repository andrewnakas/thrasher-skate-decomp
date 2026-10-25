#include "common.h"

void func_80019C0C(u8 *src, u8 *dst, s32 n) {
    s32 i = n - 1;

    if (n != 0) {
        do {
            *dst++ = *src++;
        } while (--i != -1);
    }
}
