#include "common.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVec_8002E14C;

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} Vec_8002E14C;

typedef struct Obj_8002E14C {
    u16 flags;
    u8 pad2[2];
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    struct Obj_8002E14C *next;
    u8 pad18[4];
    SVec_8002E14C *verts[4];
} Obj_8002E14C;

typedef struct {
    Obj_8002E14C *obj;
    s32 dist;
} Hit_8002E14C;

extern s16 D_8008AFC4;
extern s16 D_8008AFC6;
extern s16 D_8008AFC8;
extern s32 D_8008B064;
extern s16 D_8008B074[4];
extern Hit_8002E14C *D_8008B080;

s32 func_8002D330(Obj_8002E14C *, s32, s32, s32);
void func_8002E4B4(SVec_8002E14C *, SVec_8002E14C *, SVec_8002E14C *, SVec_8002E14C *);
void func_8002E68C(Obj_8002E14C *, s16 *);
s32 func_8002EC14(s16 *, s16 *);
s32 func_80032C28(s32, s32);
s32 func_80032C54(s32, s32);
s32 func_80032D3C(s32);

s32 func_8002E14C(Obj_8002E14C *obj) {
    s16 bb[8];
    Vec_8002E14C proj;
    union {
        Vec_8002E14C d;
        SVec_8002E14C c;
    } u;
    SVec_8002E14C out;
    s32 found;
    s32 ay;
    s32 y;
    s32 dist;
    s32 h;
    s32 r2;
    s32 i;
    SVec_8002E14C *prev;
    SVec_8002E14C *cur;

    found = 0;
    do {
        if (!(obj->flags & 0x20)) {
            y = obj->y;
            ay = abs(y);
            if (ay < 0x290) {
                dist = obj->x * D_8008AFC4 + y * D_8008AFC6 + obj->z * D_8008AFC8 + obj->w;
                h = dist >> 16;
                if (dist >= 0 && h < D_8008B064) {
                    func_8002E68C(obj, bb);
                    if (func_8002EC14(bb, D_8008B074) != 0) {
                        r2 = D_8008B064 * D_8008B064 - h * h;
                        func_80032C54(func_80032D3C(r2 << 8) << 16, 0x100000);
                        proj.vx = (D_8008AFC4 << 16) - func_80032C28(obj->x, dist);
                        proj.vy = (D_8008AFC6 << 16) - func_80032C28(obj->y, dist);
                        proj.vz = (D_8008AFC8 << 16) - func_80032C28(obj->z, dist);
                        if (func_8002D330(obj, proj.vx, proj.vy, proj.vz) != 0) {
                            goto hit;
                        }
                        i = 2;
                        if (obj->flags & 1) {
                            i = 3;
                        }
                        for (; i >= 0; i--) {
                            SVec_8002E14C *v = obj->verts[i];

                            u.d.vx = v->vx - (s16) (proj.vx >> 16);
                            u.d.vy = v->vy - (s16) (proj.vy >> 16);
                            u.d.vz = v->vz - (s16) (proj.vz >> 16);
                            if (u.d.vx * u.d.vx + u.d.vy * u.d.vy + u.d.vz * u.d.vz < r2) {
                                goto hit;
                            }
                        }
                        u.c.vx = proj.vx >> 16;
                        u.c.vy = proj.vy >> 16;
                        u.c.vz = proj.vz >> 16;
                        prev = obj->verts[0];
                        i = 2;
                        if (obj->flags & 1) {
                            i = 3;
                        }
                        for (; i >= 0; i--) {
                            cur = obj->verts[i];
                            func_8002E4B4(prev, cur, &u.c, &out);
                            out.vx -= (s16) (proj.vx >> 16);
                            out.vy -= (s16) (proj.vy >> 16);
                            out.vz -= (s16) (proj.vz >> 16);
                            if (out.vx * out.vx + out.vy * out.vy + out.vz * out.vz < r2) {
                                goto hit;
                            }
                            prev = cur;
                        }
                        goto next;
                    hit:
                        found = 1;
                        D_8008B080->obj = obj;
                        D_8008B080->dist = dist;
                        D_8008B080++;
                    }
                }
            }
        }
    next:
        obj = obj->next;
    } while (obj != NULL);
    D_8008B080->obj = NULL;
    return found;
}
