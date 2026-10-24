#include "common.h"

void VSync(s32);
s32 func_8005CBEC(s32, u8 *, s32 *);

s32 func_800361F0(void) {
    u8 buf[8];
    s32 out;

    buf[0] = 0x80;
    if (func_8005CBEC(0xE, buf, &out) == 0) {
        return 1;
    }
    VSync(0);
    VSync(0);
    VSync(0);
    VSync(0);
    return 0;
}
