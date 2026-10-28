#include "common.h"

typedef struct {
    u32 w[5];
} T_8001EB4C;

typedef struct {
    u16 f00;
    u16 f02;
    u8 pad04[0x2B];
    u8 f2F;
    u8 f30;
    u8 pad31[7];
    u32 f38;
    u32 f3C;
    u32 f40;
    u8 pad44[0x14];
} Ent_8001EB4C;

extern u8 D_8006F2C0[];

extern s32 func_8001DD58(void *);
extern void func_8001DB74(void *);
extern u8 *func_8001D870(u32);
extern void func_8004874C(u32, u32, void *, void *);

void func_8001EB4C(Ent_8001EB4C *s) {
    T_8001EB4C args;
    u8 *base;
    u8 *h;
    u8 *h2;
    u8 *t;
    s32 i;
    u32 v;
    u32 e;
    u32 f;
    u32 arg0;
    u32 arg1;
    u32 off;
    u16 flags;

    if (func_8001DD58(s) != 0) {
        if (s->f00 & 1) {
            func_8001DB74(s);
        }
        return;
    }
    if (s->f2F == 0x7F) {
        return;
    }
    h = func_8001D870(s->f02);
    base = D_8006F2C0;
    v = *(u16 *) (h + 0x10);
    h2 = h + v * 12;
    t = base + s->f02 * 0x4C;
    e = *(u16 *) (h2 + 0x1A);
    f = *(u16 *) (t + 2);
    arg1 = s->f2F + e;
    arg0 = f & 0x7FFF;
    i = 3;
    if ((f & 7) == 1) {
        args.w[0] = s->f3C;
        args.w[1] = s->f40;
        args.w[2] = s->f30;
    } else {
        off = 0x54;
        do {
            args.w[i] = (u32) ((u8 *) s + off);
            i--;
            off -= 8;
        } while (i >= 0);
    }
    args.w[4] = s->f38;
    flags = s->f00;
    if (flags & 0x200) {
        arg0 |= 0x8000;
    }
    if (flags & 0x400) {
        arg0 |= 0x4000;
    }
    if (flags & 0x800) {
        arg0 |= 0x2000;
    }
    if (flags & 0x40) {
        arg0 |= 0x200;
    }
    func_8004874C(arg0, arg1 & 0xFFFF, (u8 *) s + 0x10, args.w);
}
