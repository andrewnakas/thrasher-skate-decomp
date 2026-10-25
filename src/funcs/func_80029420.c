#include "common.h"

extern u8 *func_8001D5B0(u8 *self, u32 tag, s32 n);
extern void func_8003C1A4(u16 a, u16 b, s16 c, u8 *d);
extern u8 D_800A4F00[0x40];

void func_80029420(u8 *self, s32 unused, u8 *info) {
    u8 *e;
    u32 v;

    if ((*(u32 *) (info + 0x18) & 0x1000000) == 0) {
        return;
    }
    e = func_8001D5B0(self, 0x4F4E4150, 1);
    func_8003C1A4(*(u16 *) (e + 0xC), *(u16 *) (e + 0xE), *(s16 *) (e + 0xA), e + 0x10);
    v = *(u32 *) D_800A4F00;
    if ((v & 1) == 0) {
        *(u32 *) D_800A4F00 = v | 2;
    }
}
