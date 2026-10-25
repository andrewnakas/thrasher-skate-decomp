#include "common.h"

typedef struct {
    u8 *f0;
    s32 f4;
    u8 *f8;
} Ctx;

void func_800142B4(u8 *, s32);
void func_8001AF0C(Ctx *, u16, u16, u16, s32, u16);
void func_8001B0FC(u8 *, s32, s32);
void func_80014294(u8 *, u16, s32);
u8 *func_800123A8(u8 *);
s32 func_80032C28(s32, s32);
void func_800122CC(u8 *, s32 *);

s32 func_8001ADEC(Ctx *c, u16 arg1, u16 arg2, u16 arg3, s32 arg4) {
    u8 *p;
    u8 *t;
    u16 v;
    s32 tmp[3];

    p = c->f0;
    v = *(u16 *)(p + 0x178);
    func_800142B4(p, *(s32 *)(c->f8 + 0x10));
    func_8001AF0C(c, arg1, arg2, arg3, arg4, v);
    func_8001B0FC(c->f0, c->f4, *(s32 *)(c->f8 + 0xC));
    func_80014294(c->f0, v, arg1);
    t = func_800123A8(c->f0);
    tmp[0] = func_80032C28(*(s32 *)(c->f8 + 0x14), *(s32 *)t);
    tmp[1] = func_80032C28(*(s32 *)(c->f8 + 0x18), *(s32 *)(t + 4));
    tmp[2] = func_80032C28(*(s32 *)(c->f8 + 0x1C), *(s32 *)(t + 8));
    func_800122CC(c->f0, tmp);
    return 0;
}
