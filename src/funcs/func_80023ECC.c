#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
} Vec_80023ECC;

typedef struct {
    u8 pad0[0x44];
    Vec_80023ECC pos;
    u8 pad50[0x3C];
} Ent_80023ECC;

typedef struct {
    s32 count;
    Ent_80023ECC e[1];
} Obj_80023ECC;

typedef struct {
    u8 pad0[0x38];
    u8 *data;
} Arg_80023ECC;

void func_80026E78(u8 *);
void func_80032FE0(Vec_80023ECC *);
void func_8001446C(Arg_80023ECC *, s32, Vec_80023ECC *, Vec_80023ECC *, s32);

void func_80023ECC(Obj_80023ECC *obj, Arg_80023ECC *arg1) {
    Vec_80023ECC v;
    u8 *d;
    s32 i;

    d = arg1->data;
    func_80026E78(d + 0x2E0);
    func_80026E78(d + 0x2E6);
    func_80026E78(d + 0x2EC);
    func_80026E78(d + 0x322);
    func_80026E78(d + 0x334);
    func_80026E78(d + 0x310);
    func_80026E78(d + 0x2FE);
    func_80026E78(d + 0x2F8);
    func_80026E78(d + 0x30A);
    func_80026E78(d + 0x2F2);
    func_80026E78(d + 0x304);
    func_80026E78(d + 0x31C);
    func_80026E78(d + 0x32E);
    func_80026E78(d + 0x316);
    func_80026E78(d + 0x328);
    for (i = 0; i < obj->count; i++) {
        func_80032FE0(&v);
        switch (i) {
            case 0:
                func_8001446C(arg1, 1, &v, &obj->e[i].pos, 1);
                break;
            case 1:
                func_8001446C(arg1, 0xC, &v, &obj->e[i].pos, 1);
                break;
            case 2:
                func_8001446C(arg1, 9, &v, &obj->e[i].pos, 1);
                break;
            case 3:
                func_8001446C(arg1, 0xD, &v, &obj->e[i].pos, 1);
                break;
            case 4:
                func_8001446C(arg1, 0xA, &v, &obj->e[i].pos, 1);
                break;
            case 5:
                func_8001446C(arg1, 0xE, &v, &obj->e[i].pos, 1);
                break;
            case 6:
                func_8001446C(arg1, 0xB, &v, &obj->e[i].pos, 1);
                break;
            case 7:
                func_8001446C(arg1, 6, &v, &obj->e[i].pos, 1);
                break;
            case 8:
                func_8001446C(arg1, 3, &v, &obj->e[i].pos, 1);
                break;
            case 9:
                func_8001446C(arg1, 7, &v, &obj->e[i].pos, 1);
                break;
            case 10:
                func_8001446C(arg1, 4, &v, &obj->e[i].pos, 1);
                break;
            case 11:
                func_8001446C(arg1, 8, &v, &obj->e[i].pos, 1);
                break;
            case 12:
                func_8001446C(arg1, 5, &v, &obj->e[i].pos, 1);
                break;
            case 13:
                v.vy = -0x190000;
                func_8001446C(arg1, 2, &v, &obj->e[i].pos, 1);
                break;
        }
    }
}
