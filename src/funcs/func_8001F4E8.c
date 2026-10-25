#include "common.h"

void func_8001DB74(void);
void func_8004912C(s32, s32);

void func_8001F4E8(u8 *arg0) {
    s32 n;
    s32 *p;
    u32 v;

    v = *(u32 *)(arg0 + 0xC);
    if (v < 3) {
        if (v != 0) {
            func_8001DB74();
            return;
        }
    }
    p = *(s32 **)(arg0 + 0x2C);
    n = *p;
    *(s32 **)(arg0 + 0x2C) = p + 1;
    if (n == 0) {
        func_8001DB74();
    } else {
        func_8004912C(*(s32 *)(arg0 + 0x28), n);
    }
}
