#include "common.h"

typedef struct {
    u8 type;
    u8 pad1[3];
    s32 v[4];
} Shape_8002F054;

typedef struct {
    union {
        u32 flags;
        u16 id;
    } u;
    u8 pad4[2];
    s16 rot;
    u8 pad8[2];
    s16 x;
    s16 y;
    s16 z;
    s32 sx;
    s32 sy;
    s32 sz;
} Obj_8002F054;

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
} Vec_8002F054;

typedef struct {
    u32 flags;
    u8 pad4[0x1C];
    u16 id;
    u8 pad22[2];
    Obj_8002F054 *obj;
    Shape_8002F054 *shape;
} Hit_8002F054;

Shape_8002F054 *func_8002E8C0(u16);
void func_8002E848(s32 *, s32 *, s16);
s32 func_80032C28(s32, s32);
s32 func_80032C54(s32, s32);

s32 func_8002F054(Obj_8002F054 *o, Vec_8002F054 *pos, Hit_8002F054 *hit) {
    Shape_8002F054 *s;
    s32 r;
    s32 dx;
    s32 dz;
    s32 t;

    s = func_8002E8C0(o->u.id);
    if (o->u.flags & 0x2400000) {
        return 0x27100000;
    }
    switch (s->type) {
        case 0:
            break;
        case 1: {
            s32 *p;

            p = s->v;
            r = func_80032C28(p[0], o->sx);
            dx = pos->vx - (o->x << 16);
            dz = pos->vz - (o->z << 16);
            if (abs(dx) > r) {
                return 0x27100000;
            }
            if (abs(dz) > r) {
                return 0x27100000;
            }
            t = func_80032C28(dx, dx) + func_80032C28(dz, dz);
            if (p[2] < t) {
                return 0x27100000;
            }
            if (hit != NULL) {
                hit->flags |= 4;
                hit->id = o->u.id;
                hit->obj = o;
                hit->shape = s;
            }
            return (o->y << 16) - func_80032C28(p[1], o->sx);
        }
        case 2: {
            s32 ax;
            s32 az;
            s32 a;
            s32 b;
            s32 m;
            s32 *p;

            ax = pos->vx - (o->x << 16);
            az = pos->vz - (o->z << 16);
            a = func_80032C28(s->v[0], o->sx);
            p = s->v;
            b = func_80032C28(p[2], o->sz);
            m = b;
            if (b < a) {
                m = a;
            }
            if (abs(ax) > m) {
                return 0x27100000;
            }
            if (abs(az) > m) {
                return 0x27100000;
            }
            func_8002E848(&ax, &az, o->rot);
            if (abs(ax) > a) {
                return 0x27100000;
            }
            if (abs(az) > b) {
                return 0x27100000;
            }
            if (hit != NULL) {
                hit->flags |= 4;
                hit->id = o->u.id;
                hit->obj = o;
                hit->shape = s;
            }
            t = -p[1];
            if (p[3] != 0) {
                t += func_80032C28(func_80032C54(ax, s->v[0]), p[3]);
                t -= p[3];
            }
            return func_80032C28(t, o->sy) + (o->y << 16);
        }
        case 3: {
            s32 ax;
            s32 az;
            s32 a;
            s32 b;
            s32 m;
            s32 *p;

            ax = pos->vx - (o->x << 16);
            az = pos->vz - (o->z << 16);
            a = func_80032C28(s->v[0], o->sx);
            p = s->v;
            b = func_80032C28(p[2], o->sz);
            m = b;
            if (b < a) {
                m = a;
            }
            if (abs(ax) > m) {
                return 0x27100000;
            }
            if (abs(az) > m) {
                return 0x27100000;
            }
            func_8002E848(&ax, &az, o->rot);
            if (abs(ax) > a) {
                return 0x27100000;
            }
            if (abs(az) > b) {
                return 0x27100000;
            }
            if (hit != NULL) {
                hit->flags |= 4;
                hit->id = o->u.id;
                hit->obj = o;
                hit->shape = s;
            }
            t = -func_80032C28(p[1], func_80032C54(p[2] - abs(az), p[2]));
            if (p[3] != 0) {
                t += func_80032C28(func_80032C54(ax, s->v[0]), p[3]);
                t -= p[3];
            }
            return func_80032C28(t, o->sy) + (o->y << 16);
        }
    }
    return 0x27100000;
}
