#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
} Vec_80022968;

typedef struct {
    u8 pad0[4];
    Vec_80022968 v1;
    Vec_80022968 v2;
    Vec_80022968 v3;
} Shape_80022968;

typedef struct {
    u16 flag;
    u8 pad2[0x32];
    s32 mass;
    u8 pad38[0xC];
    Vec_80022968 pos;
} Body_80022968;

typedef struct {
    u8 pad0[4];
    Body_80022968 *a;
    Body_80022968 *b;
    Body_80022968 *c;
    Shape_80022968 *sa;
    Shape_80022968 *sb;
    s32 mode;
    s32 axisA;
    s32 axisB;
    s32 k;
} Joint_80022968;

s32 func_80032C28(s32, s32);
s32 func_80032C54(s32, s32);
void func_80032FF4(Vec_80022968 *, Vec_80022968 *);
void func_800330A4(Vec_80022968 *);
void func_800331FC(Vec_80022968 *, s32);
s32 func_8003353C(Vec_80022968 *, Vec_80022968 *);

#define GET_AXIS(out, sh, type)                \
    if ((type) == 1) {                         \
        (out).vx = (sh)->v1.vx;                \
        (out).vy = (sh)->v1.vy;                \
        (out).vz = (sh)->v1.vz;                \
    } else if ((type) == 3) {                  \
        (out).vx = (sh)->v3.vx;                \
        (out).vy = (sh)->v3.vy;                \
        (out).vz = (sh)->v3.vz;                \
    } else if ((type) == 2) {                  \
        (out).vx = (sh)->v2.vx;                \
        (out).vy = (sh)->v2.vy;                \
        (out).vz = (sh)->v2.vz;                \
    } else if ((type) == 4) {                  \
        (out).vx = (sh)->v1.vx;                \
        (out).vy = (sh)->v1.vy;                \
        (out).vz = (sh)->v1.vz;                \
        func_800331FC(&(out), -0x10000);       \
    } else if ((type) == 6) {                  \
        (out).vx = (sh)->v3.vx;                \
        (out).vy = (sh)->v3.vy;                \
        (out).vz = (sh)->v3.vz;                \
        func_800331FC(&(out), -0x10000);       \
    } else {                                   \
        (out).vx = (sh)->v2.vx;                \
        (out).vy = (sh)->v2.vy;                \
        (out).vz = (sh)->v2.vz;                \
        func_800331FC(&(out), -0x10000);       \
    }

void func_80022968(Joint_80022968 *j) {
    Vec_80022968 n;
    Vec_80022968 m;
    Vec_80022968 d;
    s32 dot;
    s32 s;
    s32 t;

    GET_AXIS(n, j->sa, j->axisA);
    GET_AXIS(m, j->sb, j->axisB);
    d.vx = j->b->pos.vx - j->c->pos.vx;
    d.vy = j->b->pos.vy - j->c->pos.vy;
    d.vz = j->b->pos.vz - j->c->pos.vz;
    dot = func_8003353C(&d, &n);
    s = -dot;
    if (j->mode == 1 && s > 0) {
        return;
    }
    if (j->mode == 2 && s < 0) {
        return;
    }
    m.vx = n.vx;
    m.vy = n.vy;
    m.vz = n.vz;
    s = func_80032C28(s, j->k);
    s = func_80032C28(s, func_80032C54(j->a->mass, j->a->mass + j->b->mass));
    func_800331FC(&n, s);
    t = func_80032C28(dot, j->k);
    t = func_80032C28(t, func_80032C54(j->b->mass, j->a->mass + j->b->mass));
    func_800331FC(&m, s);
    if (func_8003353C(&m, &m) > 0x100000) {
        func_800330A4(&m);
        func_800331FC(&m, 0x40000);
    }
    if (j->a->flag != 0) {
        func_80032FF4(&j->b->pos, &m);
    }
}
