#include "common.h"

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4_23D2C;

typedef struct {
    u8 pad0[0x38];
    s32 unk38;
    u8 pad3C[8];
    Vec4_23D2C pos;
    u8 pad54[8];
    Vec4_23D2C vel;
} Body_23D2C;

typedef struct {
    u8 pad0[4];
    s32 bias;
    Body_23D2C *a;
    Body_23D2C *b;
    s32 len;
    u8 *p14;
    u8 *p18;
    s32 k;
} Joint_23D2C;

s32 func_80032C28(s32, s32);
void func_80032FF4(Vec4_23D2C *, Vec4_23D2C *);
void func_800330A4(Vec4_23D2C *);
void func_800331FC(Vec4_23D2C *, s32);
s32 func_8003353C(void *, void *);

void func_80023D2C(Joint_23D2C *j) {
    Vec4_23D2C d;
    Vec4_23D2C t;
    Body_23D2C *a;
    Body_23D2C *b;
    Vec4_23D2C *pa;
    Vec4_23D2C *pb;
    s32 f;
    s32 pen;

    f = j->bias;
    a = j->a;
    b = j->b;
    pen = func_8003353C(j->p14 + 0x10, j->p18 + 4);
    pa = &a->pos;
    pen = -pen;
    pb = &b->pos;
    if (pen > 0) {
        f += func_80032C28(j->k, pen);
    }
    d.vx = a->pos.vx - b->pos.vx;
    d.vy = pa->vy - pb->vy;
    d.vz = pa->vz - pb->vz;
    func_800330A4(&d);
    func_800331FC(&d, j->len);
    t.vx = d.vx;
    t.vy = d.vy;
    t.vz = d.vz;
    func_80032FF4(&t, pb);
    func_800331FC(&t, f);
    func_80032FF4(&j->a->vel, &t);
    t.vx = a->pos.vx - d.vx;
    t.vy = pa->vy - d.vy;
    t.vz = pa->vz - d.vz;
    func_800331FC(&t, f);
    func_80032FF4(&j->b->vel, &t);
    j->a->unk38 += f;
    j->b->unk38 += f;
}
