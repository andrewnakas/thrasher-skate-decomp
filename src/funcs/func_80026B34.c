#include "common.h"

typedef struct {
    s32 x, y, z;
} Vec3_26B34;

s32 abs(s32);
void func_80026DEC(Vec3_26B34 *, Vec3_26B34 *, Vec3_26B34 *);
void func_80032FF4(Vec3_26B34 *, Vec3_26B34 *);
void func_800330A4(Vec3_26B34 *);
void func_800331FC(Vec3_26B34 *, s32);
s32 func_8003353C(Vec3_26B34 *, Vec3_26B34 *);
void func_800337C4(Vec3_26B34 *);

void func_80026B34(s32 unused, Vec3_26B34 *dir, Vec3_26B34 *m, Vec3_26B34 *out) {
    Vec3_26B34 t;
    s32 d;
    s32 k;

    func_800337C4(out);
    out[1].x = dir->x;
    out[1].y = dir->y;
    out[1].z = dir->z;
    func_800330A4(&out[1]);
    d = func_8003353C(m, &out[1]);
    func_8003353C(&m[1], &out[1]);
    func_8003353C(&m[2], &out[1]);
    t.x = m[2].x;
    t.y = m[2].y;
    t.z = m[2].z;
    func_80026DEC(m, &out[1], dir);
    func_800330A4(dir);
    k = 0x10000 - abs(d);
    func_800331FC(&t, abs(d));
    func_800331FC(dir, k);
    func_80032FF4(&t, dir);
    out[2].x = t.x;
    out[2].y = t.y;
    out[2].z = t.z;
    func_80026DEC(&out[1], &out[2], out);
    func_800330A4(out);
    func_80026DEC(out, &out[1], &out[2]);
    func_800330A4(&out[2]);
}
