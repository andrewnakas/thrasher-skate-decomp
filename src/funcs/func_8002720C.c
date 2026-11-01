#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
} Vec_8002720C;

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 f4[0x40];
    Vec_8002720C pos;
    Vec_8002720C prev;
    u8 pad5C[0xC];
    Vec_8002720C dir;
    u8 pad74[0x18];
} Ent_8002720C;

typedef struct {
    u32 count;
    Ent_8002720C e[34];
    u8 pad129C[0x80];
    Vec_8002720C f131C;
} Obj_8002720C;

typedef struct {
    u8 pad0[0x18];
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
} Arg_8002720C;

Vec_8002720C *func_80012238(Arg_8002720C *);
void func_800331FC(Vec_8002720C *, s32);
void func_800334D8(Vec_8002720C *, s32);
void func_80033714(s32, Vec_8002720C *, Vec_8002720C *);
void func_80033E14(s32, u8 *);

void func_8002720C(Obj_8002720C *obj, Arg_8002720C *arg1, s32 mat, Vec_8002720C *add, s32 arg4) {
    Vec_8002720C off;
    Vec_8002720C v[2][3];
    Vec_8002720C *base;
    u32 i;

    i = 0;
    base = func_80012238(arg1);
    for (; i < obj->count; i++) {
        switch (i) {
            case 0:
                off.vx = 0x1E0000;
                off.vy = 0x70000;
                off.vz = 0;
                break;
            case 1:
                off.vx = -0x1E0000;
                off.vy = 0x70000;
                off.vz = -0xA0000;
                break;
            case 2:
                off.vx = -0x1E0000;
                off.vy = 0x70000;
                off.vz = 0xA0000;
                break;
        }
        func_80033714(mat, &off, &v[0][i]);
        obj->e[i].pos.vx = v[0][i].vx + base->vx;
        obj->e[i].pos.vy = v[0][i].vy + base->vy;
        obj->e[i].pos.vz = v[0][i].vz + base->vz;
        v[1][i].vx = v[0][i].vx;
        v[1][i].vy = v[0][i].vy;
        v[1][i].vz = v[0][i].vz;
        func_800334D8(&v[1][i], arg4);
        obj->e[i].dir.vx = v[1][i].vx - v[0][i].vx;
        obj->e[i].dir.vy = v[1][i].vy - v[0][i].vy;
        obj->e[i].dir.vz = v[1][i].vz - v[0][i].vz;
        obj->e[i].dir.vx += add->vx;
        obj->e[i].dir.vy += add->vy;
        obj->e[i].dir.vz += add->vz;
        func_800331FC(&obj->e[i].dir, 0x8000);
        obj->e[i].prev.vx = obj->e[i].pos.vx;
        obj->e[i].prev.vy = obj->e[i].pos.vy;
        obj->e[i].prev.vz = obj->e[i].pos.vz;
        func_80033E14(mat, obj->e[i].f4);
        obj->e[i].f2 = 0;
    }
    obj->f131C.vx = base->vx;
    obj->f131C.vy = base->vy;
    obj->f131C.vz = base->vz;
    arg1->f1A = 0;
    arg1->f1C = 0;
    arg1->f1E = 0;
    arg1->f18 = 0;
}
