#include "common.h"

typedef struct {
    s32 x;
    s32 y;
} Pt_8001EB4C;

typedef struct {
    u16 flags;
    u16 id;
    u8 pad4[0xC];
    u8 pos[0x1F];
    u8 note;
    u8 vol;
    u8 pad31[7];
    s32 f38;
    Pt_8001EB4C pts[4];
} Ch_8001EB4C;

typedef struct {
    u8 pad0[0x10];
    u16 n;
} Inst_8001EB4C;

typedef struct {
    u8 pad0[0x1A];
    u16 base;
} Key_8001EB4C;

typedef struct {
    u8 pad0[2];
    u16 mode;
    u8 pad4[0x48];
} Tbl_8001EB4C;

typedef struct {
    union {
        struct {
            s32 a;
            s32 b;
            s32 c;
        } v;
        Pt_8001EB4C *p[4];
    } u;
    s32 d;
} Arg_8001EB4C;

extern Tbl_8001EB4C D_8006F2C0[];

extern s32 func_8001DD58(void);
extern void func_8001DB74(Ch_8001EB4C *);
extern Inst_8001EB4C *func_8001D870(u16);
extern void func_8004874C(s32, u16, void *, Arg_8001EB4C *);

void func_8001EB4C(Ch_8001EB4C *c) {
    Arg_8001EB4C arg;
    Inst_8001EB4C *in;
    u16 mode;
    u16 key;
    s32 m;
    s32 i;
    u16 fl;

    if (func_8001DD58() != 0) {
        if (c->flags & 1) {
            func_8001DB74(c);
        }
    } else if (c->note != 0x7F) {
        in = func_8001D870(c->id);
        in = (Inst_8001EB4C *)((u8 *)in + in->n * 12);
        key = ((Key_8001EB4C *)in)->base + c->note;
        mode = D_8006F2C0[c->id].mode;
        m = mode & 0x7FFF;
        if ((mode & 7) == 1) {
            arg.u.v.a = c->pts[0].x;
            arg.u.v.b = c->pts[0].y;
            arg.u.v.c = c->vol;
        } else {
            for (i = 3; i >= 0; i--) {
                arg.u.p[i] = &c->pts[i];
            }
        }
        arg.d = c->f38;
        fl = c->flags;
        if (fl & 0x200) {
            m |= 0x8000;
        }
        if (fl & 0x400) {
            m |= 0x4000;
        }
        if (fl & 0x800) {
            m |= 0x2000;
        }
        if (fl & 0x40) {
            m |= 0x200;
        }
        func_8004874C(m, key, c->pos, &arg);
    }
}
