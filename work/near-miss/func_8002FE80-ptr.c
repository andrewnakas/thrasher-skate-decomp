#include "common.h"

extern u8 *func_8002BAC0(s32 id);
extern s32 func_8002FEE0(u8 *self);

s32 func_8002FE80(u8 *self, s32 **out) {
    u8 buf[0xA8];
    u32 flags = *(u32 *) func_8002BAC0(*(u16 *) self);
    s32 *p = (s32 *) buf;

    if (!(flags & 2)) {
        return 0;
    }
    *out = p;
    return func_8002FEE0(self);
}
