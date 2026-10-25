#include "common.h"

extern void memset(void *d, s32 c, u32 n);
extern void func_8001483C(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e);

void func_80027090(u8 *self, u8 *a1, u8 *out) {
    u8 buf[0x38];

    memset(buf, 0, 6);
    func_8001483C(self, buf, a1 + 0xC, a1 + 0x18, buf + 8);
    *(u16 *) out = *(u16 *) (self + 0x1A);
    *(u16 *) (out + 2) = *(u16 *) (self + 0x1C);
    *(u16 *) (out + 4) = *(u16 *) (self + 0x1E);
    *(u16 *) (self + 0x1A) = 0;
    *(u16 *) (self + 0x1C) = 0;
    *(u16 *) (self + 0x1E) = 0;
}
