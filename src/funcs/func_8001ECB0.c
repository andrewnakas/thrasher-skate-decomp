#include "common.h"

typedef struct {
    s32 w[0x13];
    u8 used;
    u8 pad[3];
} Fx_8001ECB0;

typedef struct {
    u8 pad0[0x1C];
    u16 f1C;
    u8 pad1E[0x15C];
    u16 f17A;
} Owner_8001ECB0;

typedef struct {
    u16 flags;
    u8 type;
    u8 pad3;
    Owner_8001ECB0 *owner;
    u16 f8;
    u8 padA[2];
    s32 fC;
    s32 f10;
    s32 f14;
    u8 f18;
    u8 f19;
    u16 f1A;
    u16 f1C;
    u8 pad1E[2];
    s32 f20;
    s32 f24;
    s32 f28;
    Fx_8001ECB0 *fx;
    s32 f30;
    s32 f34;
    s32 f38;
    u16 f3C;
    u16 f3E;
    u16 f40;
    u16 f42;
    s16 f44;
    u16 f46;
} Def_8001ECB0;

typedef struct {
    u16 flags;
    u8 pad2[0xE];
    s32 pos[3];
    Owner_8001ECB0 *owner;
    u16 f20;
    u8 pad22[2];
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    u8 f34;
    u8 f35;
    u8 f36;
    u8 f37;
    u16 f38;
    u16 f3A;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 v[3];
    u16 f54;
    u16 f56;
    s16 f58;
    u16 f5A;
    u8 f5C;
    u8 pad5D[3];
    Fx_8001ECB0 *fx;
    u16 f64;
    s16 f66;
    u16 f68;
} Obj_8001ECB0;

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern s16 func_800142CC(s16, s16);
extern void func_8001446C(Owner_8001ECB0 *, u16, s32 *, s32 *, s32);
extern void func_8001E9AC(Obj_8001ECB0 *, s32);
extern void func_80033428(s32 *, s16);
extern Fx_8001ECB0 D_80092964[10];

s32 func_8001ECB0(Obj_8001ECB0 *o, Def_8001ECB0 *d) {
    Fx_8001ECB0 *slot;
    Fx_8001ECB0 *p;
    u32 i;
    u16 t;
    s32 x;
    s32 y;
    Owner_8001ECB0 *owner;

    owner = d->owner;
    if (owner != NULL && !(d->type & 4) && owner->f17A >= 2) {
        return 1;
    }
    o->flags |= d->flags & 0xF000;
    o->owner = owner;
    o->f20 = d->f8;
    x = d->fC;
    o->f28 = x;
    o->pos[0] = x;
    x = d->f10;
    o->f2C = x;
    o->pos[1] = x;
    x = d->f14;
    o->f30 = x;
    o->pos[2] = x;
    o->f24 = 0;
    o->f5C = d->type;
    o->f34 = d->f18;
    o->f35 = 0;
    o->f36 = d->f19;
    o->f37 = 0;
    o->f38 = d->f1A;
    o->f3A = d->f1C;
    o->f3C = d->f20;
    o->f40 = d->f24;
    o->f44 = d->f28;
    o->v[0] = d->f30;
    o->v[1] = d->f34;
    o->v[2] = d->f38;
    o->f54 = d->f3C;
    o->f56 = d->f3E;
    t = d->f40;
    o->f5A = t;
    o->f58 = ((t << 9) + 0xA0) / 320;
    o->f64 = d->f42;
    o->f66 = func_800142CC(0, d->f44);
    o->f68 = d->f46;
    if (o->owner != NULL) {
        func_80033428(o->v, (o->owner->f1C - 0x8000) * -1);
        if (o->flags & 0x6000) {
            o->v[0] = abs(o->v[0]);
            o->v[1] = abs(o->v[1]);
            o->v[2] = abs(o->v[2]);
        }
        if (o->f20 != 0xFF) {
            if (o->flags & 0x1000) {
                func_8001446C(o->owner, o->f20, o->pos, o->pos, 5);
            } else {
                func_8001446C(o->owner, o->f20, o->pos, o->pos, 1);
            }
        }
    }
    func_8001E9AC(o, 0);
    slot = NULL;
    if (d->type & 2) {
        for (i = 0, p = D_80092964; i < 10; i++, p++) {
            if (p->used == 0) {
                slot = p;
                break;
            }
        }
        if (slot != NULL) {
            *slot = *d->fx;
            o->fx = slot;
            slot->used = 1;
        }
    }
    return 0;
}
