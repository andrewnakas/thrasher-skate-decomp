#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[6];
} Vtx29CCC;

typedef struct {
    u8 pad0[0x48];
    Vtx29CCC *verts;
} Obj29CCC;

typedef struct {
    u16 idx[4];
    s16 v[3];
    u8 padE[2];
    s32 w10;
    s32 w14;
    u16 h18;
    u16 h1A;
} Src29CCC;

typedef struct {
    s32 p[4][3];
    s32 v[3];
    s32 w3C;
    s32 w40;
    u16 h44;
    u16 h46;
} Dst29CCC;

void func_80029CCC(Obj29CCC *o, s32 a1, Src29CCC *s, Dst29CCC *d) {
    u32 i;
    Vtx29CCC *v;

    for (i = 0; i < 3; i++) {
        if (s->idx[i] != 0) {
            v = &o->verts[s->idx[i]] - 1;
        } else {
            v = 0;
        }
        if (v != 0) {
            d->p[i][0] = v->x << 16;
            d->p[i][1] = v->y << 16;
            d->p[i][2] = v->z << 16;
        }
    }
    d->v[0] = s->v[0] << 16;
    d->v[1] = s->v[1] << 16;
    d->v[2] = s->v[2] << 16;
    d->w3C = s->w14;
    d->w40 = s->w10;
    d->h44 = s->h18;
    d->h46 = s->h1A;
}
