#include "common.h"

void func_8002AAA8(u16 *p, s32 a1) {
    if (p == 0) {
        return;
    }
    if (a1 != 0) {
        *p = *p & 0xFFFE;
    } else {
        *p |= 1;
    }
}
