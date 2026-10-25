#include "common.h"

extern void func_8001DB74(u8 *);

s32 func_8001E900(u8 *self, s32 *node) {
    s32 *cur = *(s32 **)(self + 0x24);
    s32 *prev = 0;

    while (cur != node) {
        prev = cur;
        cur = (s32 *) cur[0];
    }
    if (prev) {
        prev[0] = cur[0];
    } else {
        *(s32 **)(self + 0x24) = (s32 *) cur[0];
    }
    node[1] = 0;
    if (--*(u8 *)(self + 0x35)) {
        return 0;
    }
    if (*(u16 *)(self + 0x56)) {
        return 0;
    }
    if (!(*(u16 *)self & 1)) {
        return 0;
    }
    func_8001DB74(self);
    return 1;
}
