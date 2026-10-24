#include "common.h"

s32 func_80037C20(u8 *p, u16 n) {
    s32 sum = 0;

    if (n != 0) {
        do {
            sum += *p++;
            n--;
        } while (n != 0);
    }
    return sum & 0xFF;
}
