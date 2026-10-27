#include "common.h"

typedef struct {
    u16 f0;
    u16 f1;
    u16 f2;
    u16 f3;
    u16 f4;
    u16 f5;
    u16 f6;
    u8 b0;
    u8 b1;
} R_8002921C;

extern u8 *func_8001D5B0(u8 *a, u32 id, s32 b);
extern u8 *func_80034C20(u32 bytes);

void func_8002921C(u8 *bank, u8 *list, u8 *src) {
    u8 *p;
    R_8002921C *d;
    R_8002921C *s;
    s32 i;

    if ((*(u32 *)(src + 0x18) & 0x200000) == 0) {
        return;
    }
    p = func_8001D5B0(bank, 0x444E5342, 1);
    *(u16 *)(list + 0x22) = *(u16 *)(p + 0xA);
    *(u32 *)list |= 8;
    d = (R_8002921C *)func_80034C20(*(u16 *)(p + 0xA) * 16);
    *(u8 **)(list + 0x14) = (u8 *)d;
    s = (R_8002921C *)(p + 0xC);
    for (i = *(u16 *)(p + 0xA) - 1; i >= 0; i--) {
        d->f1 = s->f1;
        d->f0 = s->f0;
        d->f2 = s->f2;
        d->f3 = s->f3;
        d->f4 = s->f4;
        d->f5 = s->f5;
        d->f6 = s->f6;
        d->b0 = s->b0;
        d->b1 = s->b1;
        d++;
        s++;
    }
}
