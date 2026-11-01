#include "common.h"

typedef struct {
    s32 vx, vy, vz;
} Delta_8003012C;

typedef struct {
    s16 x, y, z, pad;
} Vtx_8003012C;

typedef struct {
    u8 pad0[4];
    s32 nx;
    s32 ny;
    s32 nz;
    s32 d;
    u8 pad14[8];
    Vtx_8003012C *pt;
    u8 pad20[0xC];
} Plane_8003012C;

typedef struct {
    s16 unk0;
    s16 a[3];
    s16 b[3];
    u8 pad[0xE];
} Tri_8003012C;

typedef struct {
    u16 id;
    u8 pad2[0x22];
    Tri_8003012C *tri;
    s16 ntri;
    u8 pad2A[6];
    s16 pos[3];
    u8 pad36[0xE];
    Vtx_8003012C vtx[8];
    Plane_8003012C plane[1];
} Obj_8003012C;

typedef struct {
    s32 nvtx;
    s32 nplane;
} Count_8003012C;

extern u8 *func_8002E8C0(u16);
extern Count_8003012C D_8006F890[];

void func_8003012C(Obj_8003012C *o, Delta_8003012C *dv) {
    u8 k;
    s32 nv;
    s32 np;
    s32 i;
    Tri_8003012C *t;

    k = *func_8002E8C0(o->id);
    nv = D_8006F890[k].nvtx;
    np = D_8006F890[k].nplane;
    for (i = 0; i < nv; i++) {
        o->vtx[i].x += (dv->vx >> 16);
        o->vtx[i].y += (dv->vy >> 16);
        o->vtx[i].z += (dv->vz >> 16);
    }
    for (i = 0; i < np; i++) {
        Plane_8003012C *p = &o->plane[i];
        Vtx_8003012C *v = p->pt;

        p->d = -(p->nx * v->x) - (p->ny * v->y) - (p->nz * v->z);
    }
    o->pos[0] += (dv->vx >> 16);
    o->pos[1] += (dv->vy >> 16);
    o->pos[2] += (dv->vz >> 16);
    i = o->ntri;
    if (i != 0) {
        i--;
        t = o->tri;
        while (i != -1) {
            t->a[0] += (dv->vx >> 16);
            t->a[1] += (dv->vy >> 16);
            t->a[2] += (dv->vz >> 16);
            t->b[0] += (dv->vx >> 16);
            t->b[1] += (dv->vy >> 16);
            t->b[2] += (dv->vz >> 16);
            i--;
            t++;
        }
    }
}
