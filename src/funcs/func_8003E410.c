/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    s32 w;
    u16 h;
} Pair_3E410;

typedef struct {
    u8 pad0[0x1C];
    Pair_3E410 *f1C;
    Pair_3E410 *f20;
    Pair_3E410 *f24;
    Pair_3E410 *f28;
    s32 f2C;
    s32 f30;
} Obj_3E410;

typedef struct {
    Obj_3E410 *obj;
    u32 key;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
} Ent_3E410;

typedef struct {
    s32 w0;
    u16 h4;
    u16 h6;
    s32 f8;
    s32 fC;
    s32 f10;
    u16 h14;
    u16 h16;
    s32 f18;
    s32 f1C;
    s32 f20;
    u16 h24;
    u16 h26;
    s32 f28;
    s32 f2C;
    s32 f30;
    u16 h34;
    u16 h36;
    s32 f38;
    s32 f3C;
} Prim_3E410;

typedef struct {
    s32 f00;
    s32 f04;
    u8 pad08[0x1C];
    s32 f24;
    s32 f28;
    s32 *f2C;
    s32 f30;
    Prim_3E410 prim;
    u8 pad74[0x15C - 0x74];
    s32 *f15C;
    s32 *f160;
} Spad_3E410;

#define SPAD ((Spad_3E410 *) 0x1F800000)

void func_80034D4C(void *, void *, s32);
void func_8003DDAC(Prim_3E410 *, void *, void *, void *);
void func_8003E7A0(Prim_3E410 *, void *, void *, void *);
extern u8 D_80082500[];
extern u8 D_80082510[];
extern Ent_3E410 *D_8008B328;
extern Ent_3E410 *D_8008B32C;
extern Ent_3E410 *D_8008B330;
extern s32 *D_8008B3A0[];

s32 func_8003E410(s32 arg) {
    s32 *slot;
    Ent_3E410 *e;
    Obj_3E410 *o;
    Prim_3E410 *p;
    u32 v;
    s32 a, b;
    Spad_3E410 *sp;

    func_80034D4C((void *) 0x1F800008, D_80082500, 0x10);
    func_80034D4C((void *) 0x1F800018, D_80082510, 0xC);
    sp = SPAD;
    sp->f2C = (s32 *) 0x1F800030;
    sp->f04 = 0;
    sp->f28 = arg;
    e = D_8008B330;
    for (e--; e >= D_8008B328; e--) {
        p = &sp->prim;
        o = e->obj;
        p->fC = e->f08;
        sp->prim.w0 = o->f1C->w;
        p->h4 = o->f1C->h;
        p->f8 = e->f20;
        p->f1C = e->f0C;
        p->f10 = o->f20->w;
        p->h14 = o->f20->h;
        p->f18 = e->f24;
        p->f2C = e->f10;
        p->f28 = e->f28;
        a = e->f1C;
        b = e->f18;
        sp->f24 = a;
        sp->f00 = b;
        slot = &D_8008B3A0[0][e->key >> 16];
        sp->f30 = *slot;
        v = o->f2C;
        p->h6 = v;
        p->h16 = v >> 16;
        v = o->f30;
        p->h26 = v >> 16;
        p->f20 = o->f28->w;
        p->h24 = o->f28->h;
        p->f3C = e->f14;
        p->f30 = o->f24->w;
        p->h34 = o->f24->h;
        p->h36 = v;
        p->f38 = e->f2C;
        sp->f160 = (s32 *) ((u8 *) sp + 0x74);
        sp->f15C = (s32 *) ((u8 *) sp + 0x114);
        func_8003DDAC(p, (u8 *) sp + 0x44, (u8 *) sp + 0x54, (u8 *) sp + 0x64);
        *slot = sp->f30;
    }
    for (e = (Ent_3E410 *) ((u8 *) D_8008B328 + 0x23D0); D_8008B32C < e; e--) {
        p = &sp->prim;
        o = e->obj;
        p->fC = e->f08;
        sp->prim.w0 = o->f1C->w;
        p->h4 = o->f1C->h;
        p->f8 = e->f20;
        p->f1C = e->f0C;
        p->f10 = o->f20->w;
        p->h14 = o->f20->h;
        p->f18 = e->f24;
        p->f2C = e->f10;
        p->f28 = e->f28;
        a = e->f1C;
        b = e->f18;
        sp->f24 = a;
        sp->f00 = b;
        slot = &D_8008B3A0[0][e->key >> 16];
        sp->f30 = *slot;
        v = (u32) o->f28;
        p->h6 = v;
        p->h16 = v >> 16;
        p->h26 = *(u16 *) &o->f2C;
        p->f20 = o->f24->w;
        p->h24 = o->f24->h;
        sp->f160 = (s32 *) ((u8 *) sp + 0x64);
        func_8003E7A0(p, (u8 *) sp + 0x44, (u8 *) sp + 0x54, (u8 *) sp + 0x114);
        *slot = sp->f30;
    }
    return sp->f28;
}
