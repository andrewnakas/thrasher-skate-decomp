#include "common.h"

void func_8003B6DC(s32, s32);
void func_8001DB74(void *);

void func_8001F3D4(u8 *arg0) {
    u32 state;
    u8 *p;
    u8 c;
    u8 d;

    state = *(u32 *)(arg0 + 0xC);
    if (state < 3) {
        if (state != 0) {
            goto zero;
        }
    }
    p = *(u8 **)(arg0 + 0x24);
    c = *p;
    p++;
    *(u8 **)(arg0 + 0x24) = p;
    if (c == 0x80) {
zero:
        func_8003B6DC(0, 0);
        func_8001DB74(arg0);
        return;
    }
    d = *p;
    *(u8 **)(arg0 + 0x24) = p + 1;
    func_8003B6DC((s8)c, (s8)d);
}
