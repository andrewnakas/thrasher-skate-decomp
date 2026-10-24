#include "common.h"

void func_80014294(u8 *arg0, u16 arg1, s16 arg2) {
    u8 *slot = arg0 + arg1 * 16;
    *(s16 *)(slot + 0x180) = arg2;
    if (arg1 == 0) {
        *(s16 *)(arg0 + 0x160) = arg2;
    }
}
