#include "common.h"

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4_2DAE8;

typedef struct {
    s16 vx, vy, vz;
} SVec_2DAE8;

typedef struct {
    u8 pad0[4];
    s32 nx, ny, nz;
    s32 d;
    u8 pad14[8];
    SVec_2DAE8 *p0;
    SVec_2DAE8 *p1;
    SVec_2DAE8 *p2;
} Plane_2DAE8;

void func_800330A4(Vec4_2DAE8 *);

void func_8002DAE8(Plane_2DAE8 *pl) {
    Vec4_2DAE8 a;
    Vec4_2DAE8 b;
    Vec4_2DAE8 n;
    SVec_2DAE8 *p0;
    SVec_2DAE8 *p1;
    SVec_2DAE8 *o;

    p1 = pl->p1;
    o = pl->p2;
    p0 = pl->p0;
    a.vx = p1->vx - o->vx;
    a.vy = p1->vy - o->vy;
    a.vz = p1->vz - o->vz;
    b.vx = p0->vx - o->vx;
    b.vy = p0->vy - o->vy;
    b.vz = p0->vz - o->vz;
    n.vx = a.vy * b.vz - b.vy * a.vz;
    n.vy = b.vx * a.vz - a.vx * b.vz;
    n.vz = a.vx * b.vy - b.vx * a.vy;
    func_800330A4(&n);
    pl->nx = n.vx;
    pl->ny = n.vy;
    pl->nz = n.vz;
    pl->d = -(pl->nx * o->vx) - pl->ny * o->vy - pl->nz * o->vz;
}
