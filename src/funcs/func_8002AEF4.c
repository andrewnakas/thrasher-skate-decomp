#include "common.h"

typedef struct {
    u32 flags;
    u8 pad04[6];
    s16 hA;
    s16 hC;
    s16 hE;
    u32 f10;
    u32 f14;
    u32 f18;
    u8 *f1C;
    u8 pad20[0xC];
    u32 f2C;
} Obj_8002AEF4;

extern u8 *func_8001BDEC(u32 a0, s32 *a1, u8 *a2);
extern void func_800122CC(u8 *a0, s32 *a1);
extern void func_800142B4(u8 *a0, u32 a1);
extern u8 *func_8002BAC0(u32 a0);
extern void func_80014310(u8 *a0);

void func_8002AEF4(Obj_8002AEF4 *o) {
    s32 a[3];
    s32 b[3];
    u8 *p;
    u32 v;

    if (o->flags & 0x1000000) {
        return;
    }
    if (o->f1C != NULL) {
        return;
    }
    a[0] = (s32) o->hA << 16;
    a[1] = (s32) o->hC << 16;
    a[2] = (s32) o->hE << 16;
    o->f1C = func_8001BDEC((u16) o->flags, a, (u8 *) o + 4);
    b[0] = o->f10;
    b[1] = o->f14;
    b[2] = o->f18;
    func_800122CC(o->f1C, b);
    func_800142B4(o->f1C, o->f2C);
    p = func_8002BAC0((u16) o->flags);
    if (*(u32 *) p & 0x80) {
        v = *(u32 *) (o->f1C + 0x3C);
        *(u32 *) (o->f1C + 0x3C) = v | 0x40;
    }
    if (*(u32 *) p & 0x100) {
        v = *(u32 *) (o->f1C + 0x3C);
        *(u32 *) (o->f1C + 0x3C) = v | 0x80;
    }
    if (*(u32 *) p & 0x40) {
        o->flags |= 0x400000;
    }
    if (o->flags & 0x2000000) {
        func_80014310(o->f1C);
    }
}
