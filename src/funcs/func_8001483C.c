#include "common.h"

typedef struct {
    s32 x, y, z, pad;
} Vec_8001483C;

typedef struct {
    s32 x, y, z;
} Vec3_8001483C;

typedef struct {
    s16 m[3][3];
    s32 t[3];
} Mat_8001483C;

typedef struct {
    Vec3_8001483C r[3];
} Basis_8001483C;

extern s16 D_80089F50;
extern s32 D_80089F54;

extern s32 func_8003353C(Vec_8001483C *, Vec_8001483C *);
extern void func_800335B4(Vec_8001483C *, Vec_8001483C *, Vec_8001483C *, Vec_8001483C *);
extern void func_800330A4(void *);
extern void func_800337C4(void *);
extern void func_80033A18(Mat_8001483C *, s16);
extern void func_80033DB0(Mat_8001483C *, s32);
extern void func_80032B1C(Basis_8001483C *, Mat_8001483C *);
extern void func_80014AE8(s32, Basis_8001483C *);

void func_8001483C(s32 cam, s32 roll, Vec3_8001483C *fwd, Vec3_8001483C *up, Basis_8001483C *out) {
    Vec_8001483C side;
    Vec_8001483C f;
    Vec_8001483C u;
    Vec_8001483C zero;
    Mat_8001483C rz;
    Vec_8001483C v1;
    Mat_8001483C m;
    Vec_8001483C v2;
    Vec_8001483C *pu;
    Vec_8001483C *pf;
    u16 ang;
    s32 d;

    ang = 0;
    pu = &u;
    pf = &f;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    f.x = fwd->x;
    f.y = fwd->y;
    f.z = fwd->z;
    f.x = -f.x;
    f.y = -f.y;
    f.z = -f.z;
    u.x = up->x;
    u.y = up->y;
    u.z = up->z;
    d = func_8003353C(pf, pu);
    if (d < 0) {
        d = -d;
    }
    if (d < 0x28F) {
        func_800335B4(&side, &zero, pu, pf);
        d = func_8003353C(pu, pu) - 1;
        if (d < 0) {
            d = -d;
        }
        if (d >= 0x290) {
            goto norm;
        }
    } else {
        func_800335B4(&side, &zero, pu, pf);
        func_800335B4(pu, &zero, pf, &side);
    norm:
        func_800330A4(pu);
    }
    func_800330A4(&side);
    func_800337C4(&rz);
    if (D_80089F50 != 0) {
        if (D_80089F54 != 0) {
            ang = D_80089F50;
        } else {
            ang = -D_80089F50;
        }
        func_80033A18(&rz, ang);
    }
    func_800337C4(&m);
    func_80033DB0(&m, roll);
    func_800337C4(out);
    out->r[0].x = u.x;
    out->r[0].y = u.y;
    out->r[0].z = u.z;
    out->r[1].x = f.x;
    out->r[1].y = f.y;
    out->r[1].z = f.z;
    out->r[2].x = side.x;
    out->r[2].y = side.y;
    out->r[2].z = side.z;
    func_80032B1C(out, &m);
    if (D_80089F50 != 0) {
        func_80032B1C(out, &rz);
    }
    func_80014AE8(cam, out);
    if (D_80089F50 != 0) {
        func_800337C4(&rz);
        func_80033A18(&rz, -ang);
        func_80032B1C(out, &rz);
    }
    out->r[1].x = -out->r[1].x;
    out->r[1].y = -out->r[1].y;
    out->r[1].z = -out->r[1].z;
    func_800330A4(&out->r[1]);
}
