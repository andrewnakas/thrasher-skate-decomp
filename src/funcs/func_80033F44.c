#include "common.h"

s32 func_80033F44(const u8 *p, s32 n) {
    s32 s = 0;

    while (n > 0) {
        s += *p++;
        n--;
    }
    return s;
}
