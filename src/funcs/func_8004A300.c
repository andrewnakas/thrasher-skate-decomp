#include "common.h"

typedef struct {
    s16 x, y, z, pad;
    u8 r, g, b, cd;
} Vtx;

typedef struct {
    u32 r : 8;
    u32 g : 8;
    u32 b : 8;
    u32 cd : 8;
} Col;

typedef struct {
    s32 x : 16;
    s32 z : 16;
} P2;

typedef struct {
    u16 flags;
    u8 pad[0x1A];
    Vtx *v[4];
} Poly;

typedef struct {
    s32 x, y, z;
} Pt;

extern int abs(int);

u32 func_8004A300(Poly *poly, Pt *pt) {
    Vtx *v[4];
    s32 t[2];
    s32 t2[2];
    Vtx *ea[2];
    Vtx *eb[2];
    union {
        Col c;
        u32 w;
    } u1;
    Col c2;
    P2 p1, p2;
    s32 dx, dz, a, b;

    if (poly->flags & 1) {
        v[0] = poly->v[0];
        v[1] = poly->v[1];
        v[2] = poly->v[2];
        v[3] = poly->v[3];
        dx = v[1]->x - v[0]->x;
        dz = v[1]->z - v[0]->z;
        if (abs(dx) > abs(dz)) {
            s32 x3, z3;
            z3 = v[3]->z;
            x3 = v[3]->x;
            dx = v[2]->x - x3;
            dz = v[0]->z - z3;
            x3 = (pt->x >> 16) - x3;
            b = (pt->z >> 16) - z3;
            if (dz == 0) {
                dz = 1;
            }
            if (abs(x3) < abs(b * dx / dz)) {
                v[0] = poly->v[0];
                v[1] = poly->v[1];
                v[2] = poly->v[3];
            } else {
                v[0] = poly->v[1];
                v[1] = poly->v[3];
                v[2] = poly->v[2];
            }
        } else {
            s32 x3, z3;
            z3 = v[3]->z;
            x3 = v[3]->x;
            dz = v[2]->z - z3;
            dx = v[0]->x - x3;
            z3 = (pt->z >> 16) - z3;
            b = (pt->x >> 16) - x3;
            if (dx == 0) {
                dx = 1;
            }
            if (abs(z3) < abs(b * dz / dx)) {
                v[0] = poly->v[0];
                v[1] = poly->v[1];
                v[2] = poly->v[3];
            } else {
                v[0] = poly->v[1];
                v[1] = poly->v[3];
                v[2] = poly->v[2];
            }
        }
    } else {
        v[0] = poly->v[0];
        v[1] = poly->v[1];
        v[2] = poly->v[2];
    }

    if (v[1]->z < v[0]->z) {
        *(s32 *)&v[0] ^= (s32)v[1];
        *(s32 *)&v[1] ^= (s32)v[0];
        *(s32 *)&v[0] ^= (s32)v[1];
    }
    if (v[2]->z < v[1]->z) {
        *(s32 *)&v[2] ^= (s32)v[1];
        *(s32 *)&v[1] ^= (s32)v[2];
        *(s32 *)&v[2] ^= (s32)v[1];
    }
    if (v[1]->z < v[0]->z) {
        *(s32 *)&v[1] ^= (s32)v[0];
        *(s32 *)&v[0] ^= (s32)v[1];
        *(s32 *)&v[1] ^= (s32)v[0];
    }

    if (v[1]->z < (pt->z >> 16)) {
        ea[0] = v[1];
        ea[1] = v[2];
        eb[0] = v[0];
        eb[1] = v[2];
    } else {
        ea[1] = v[1];
        ea[0] = v[0];
        eb[0] = v[0];
        eb[1] = v[2];
    }

    dx = ea[0]->x - ea[1]->x;
    dz = ea[0]->z - ea[1]->z;
    if (abs(dx) > abs(dz)) {
        t[0] = ((ea[0]->x << 16) - pt->x) / dx;
    } else {
        t[0] = ((ea[0]->z << 16) - pt->z) / dz;
    }
    u1.c.r = ea[0]->r - (((ea[0]->r - ea[1]->r) * t[0]) >> 16);
    u1.c.g = ea[0]->g - (((ea[0]->g - ea[1]->g) * t[0]) >> 16);
    u1.c.b = ea[0]->b - (((ea[0]->b - ea[1]->b) * t[0]) >> 16);
    p1.x = ea[0]->x - (((ea[0]->x - ea[1]->x) * t[0]) >> 16);
    p1.z = ea[0]->z - (((ea[0]->z - ea[1]->z) * t[0]) >> 16);

    dx = eb[0]->x - eb[1]->x;
    dz = eb[0]->z - eb[1]->z;
    if (abs(dx) > abs(dz)) {
        t[0] = ((eb[0]->x << 16) - pt->x) / dx;
    } else {
        t[0] = ((eb[0]->z << 16) - pt->z) / dz;
    }
    c2.r = eb[0]->r - (((eb[0]->r - eb[1]->r) * t[0]) >> 16);
    c2.g = eb[0]->g - (((eb[0]->g - eb[1]->g) * t[0]) >> 16);
    c2.b = eb[0]->b - (((eb[0]->b - eb[1]->b) * t[0]) >> 16);
    p2.x = eb[0]->x - (((eb[0]->x - eb[1]->x) * t[0]) >> 16);
    p2.z = eb[0]->z - (((eb[0]->z - eb[1]->z) * t[0]) >> 16);

    dx = p2.x - p1.x;
    dz = p2.z - p1.z;
    if (abs(dx) > abs(dz)) {
        t2[0] = ((p2.x << 16) - pt->x) / dx;
    } else if (dz != 0) {
        t2[0] = ((p2.z << 16) - pt->z) / dz;
    } else {
        t2[0] = 0x10000;
    }
    u1.c.r = c2.r - (((c2.r - u1.c.r) * t2[0]) >> 16);
    u1.c.g = c2.g - (((c2.g - u1.c.g) * t2[0]) >> 16);
    u1.c.b = c2.b - (((c2.b - u1.c.b) * t2[0]) >> 16);
    return u1.w;
}
