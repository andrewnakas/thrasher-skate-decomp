#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} Vec11D60;

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVec11D60;

typedef struct {
    s32 eye[3];
    s32 at[3];
    s32 dir[3];
    u8 pad24[4];
    u8 mat[0x24];
    s32 trans[3];
} Cam11D60;

extern Cam11D60 *D_8008ACA0;

void func_800330A4(s32 *);
s32 func_80032D88(s32);
s32 func_80032DCC(s32, s32);
void func_800337C4(void *);
void func_80033A18(void *, s32);
void func_8003384C(void *, s32);
void func_80033714(void *, Vec11D60 *, Vec11D60 *);
void func_8003BF7C(void);

void func_80011D60(Vec11D60 *a, Vec11D60 *b) {
    SVec11D60 rot;
    Vec11D60 out;
    Vec11D60 eye;
    Vec11D60 at;

    eye.vx = a->vx;
    eye.vy = a->vy;
    eye.vz = a->vz;
    at.vx = b->vx;
    at.vy = b->vy;
    at.vz = b->vz;
    D_8008ACA0->eye[0] = eye.vx;
    D_8008ACA0->eye[1] = eye.vy;
    D_8008ACA0->eye[2] = eye.vz;
    D_8008ACA0->at[0] = at.vx;
    D_8008ACA0->at[1] = at.vy;
    D_8008ACA0->at[2] = at.vz;
    D_8008ACA0->dir[0] = at.vx - eye.vx;
    D_8008ACA0->dir[1] = at.vy - eye.vy;
    D_8008ACA0->dir[2] = at.vz - eye.vz;
    func_800330A4(D_8008ACA0->dir);
    rot.vx = 0x4000 - func_80032D88(D_8008ACA0->dir[1]);
    rot.vy = -func_80032DCC(D_8008ACA0->dir[0], D_8008ACA0->dir[2]);
    rot.vz = 0;
    func_800337C4(D_8008ACA0->mat);
    func_80033A18(D_8008ACA0->mat, rot.vy);
    func_8003384C(D_8008ACA0->mat, rot.vx);
    func_80033714(D_8008ACA0->mat, &eye, &out);
    D_8008ACA0->trans[0] = -out.vx;
    D_8008ACA0->trans[1] = -out.vy;
    D_8008ACA0->trans[2] = -out.vz;
    func_8003BF7C();
}
