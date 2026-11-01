#include "common.h"

typedef struct {
    u32 u0 : 8;
    u32 v0 : 8;
    u32 u1 : 8;
    u32 v1 : 8;
} UV4_8002A564;

typedef struct {
    u16 u : 8;
    u16 v : 8;
} UV2_8002A564;

typedef struct {
    u16 flags;
    u8 pad2[0x26];
    UV4_8002A564 uv28;
    union {
        struct {
            UV4_8002A564 a;
            UV4_8002A564 b;
        } q;
        UV2_8002A564 t;
    } uv2C;
} Obj_8002A564;

extern u16 *func_8004659C(u16);
extern s16 func_80047420(u16);
extern u8 func_80047460(u16);

void func_8002A564(Obj_8002A564 *p, s32 to, s32 from) {
    s32 mask;
    s32 shift;
    s32 du;
    s32 dv;
    s32 m;
    UV4_8002A564 a;
    union {
        UV4_8002A564 q;
        UV2_8002A564 t;
    } b;

    if (p->flags & 2) {
        m = *func_8004659C(from) & 0x180;
        if (m == 0) {
            mask = 0xFF;
            shift = 2;
        } else if (m == 0x80) {
            mask = 0x7F;
            shift = 1;
        } else {
            mask = 0x3F;
            shift = 0;
        }
        if (p->flags & 1) {
            du = (func_80047420(from) << shift) & mask;
            dv = func_80047460(from);
            a = p->uv2C.q.a;
            b.q = p->uv2C.q.b;
            a.u0 -= du;
            a.v0 -= dv;
            a.u1 -= du;
            a.v1 -= dv;
            b.q.u0 -= du;
            b.q.v0 -= dv;
            b.q.u1 -= du;
            b.q.v1 -= dv;
            du = (func_80047420(to) << shift) & mask;
            dv = func_80047460(to);
            a.u0 += du;
            a.v0 += dv;
            a.u1 += du;
            a.v1 += dv;
            b.q.u0 += du;
            b.q.v0 += dv;
            b.q.u1 += du;
            b.q.v1 += dv;
            p->uv2C.q.a = a;
            p->uv2C.q.b = b.q;
        } else {
            du = (func_80047420(from) << shift) & mask;
            dv = func_80047460(from);
            a = p->uv28;
            b.t = p->uv2C.t;
            a.u0 -= du;
            a.v0 -= dv;
            a.u1 -= du;
            a.v1 -= dv;
            b.q.u0 -= du;
            b.q.v0 -= dv;
            du = (func_80047420(to) << shift) & mask;
            dv = func_80047460(to);
            a.u0 += du;
            a.v0 += dv;
            a.u1 += du;
            a.v1 += dv;
            b.q.u0 += du;
            b.q.v0 += dv;
            p->uv28 = a;
            p->uv2C.t = b.t;
        }
    }
}
