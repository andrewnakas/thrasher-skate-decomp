#include "common.h"

typedef struct {
    s16 v[3];
} SV;

typedef struct {
    u16 flags;
    u8 pad2[2];
    s32 n[3];
    u8 pad10[0xC];
    SV *vt[4];
} Poly;

s32 func_8002D330(Poly *p, s32 x, s32 y, s32 z) {
    s32 pt[3];
    s32 d[3];
    s32 e[3];
    s32 ax;
    s32 ay;
    s32 az;
    s32 axis;
    s32 i;
    s32 sign;
    s32 cross;
    SV *prev;
    SV *cur;

    pt[0] = x >> 16;
    pt[1] = y >> 16;
    pt[2] = z >> 16;
    ax = abs(p->n[0]);
    ay = abs(p->n[1]);
    if (ax >= ay) {
        axis = (ax < abs(p->n[2])) ? 2 : 0;
    } else {
        axis = (ay >= abs(p->n[2])) ? 1 : 2;
    }
    i = 2;
    sign = ((s32 *) p)[axis + 1];
    prev = p->vt[0];
    if (p->flags & 1) {
        i = 3;
    }
    for (; i >= 0; i--) {
        cur = p->vt[i];
        if (axis == 0) {
            d[1] = prev->v[1] - cur->v[1];
            d[2] = prev->v[2] - cur->v[2];
            e[1] = pt[1] - cur->v[1];
            e[2] = pt[2] - cur->v[2];
            cross = d[2] * e[1] - d[1] * e[2];
            if (cross != 0) {
                if ((cross ^ sign) < 0) {
                    return 0;
                }
            }
        } else if (axis == 1) {
            d[0] = prev->v[0] - cur->v[0];
            d[2] = prev->v[2] - cur->v[2];
            e[0] = pt[0] - cur->v[0];
            e[2] = pt[2] - cur->v[2];
            cross = d[0] * e[2] - d[2] * e[0];
            if (cross != 0) {
                if ((cross ^ sign) < 0) {
                    return 0;
                }
            }
        } else {
            d[0] = prev->v[0] - cur->v[0];
            d[1] = prev->v[1] - cur->v[1];
            e[0] = pt[0] - cur->v[0];
            e[1] = pt[1] - cur->v[1];
            cross = d[1] * e[0] - d[0] * e[1];
            if (cross != 0) {
                if ((cross ^ sign) < 0) {
                    return 0;
                }
            }
        }
        prev = cur;
    }
    return 1;
}
