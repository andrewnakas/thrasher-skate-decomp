#include "common.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SV_8002F810;

typedef struct {
    s32 r;
    s32 x;
    s32 y;
    s32 z;
} Sub_8002F810;

typedef struct {
    u8 type;
    u8 pad1[3];
    Sub_8002F810 s;
} Shape_8002F810;

typedef struct {
    u16 id;
    u8 pad2[4];
    u16 rot;
    u8 pad8[2];
    s16 px;
    s16 py;
    s16 pz;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0x10];
    s32 unk2C;
    u8 pad30[0x14];
    SV_8002F810 v[8];
    u8 sub[5][0x2C];
} Obj_8002F810;

extern u8 D_8006F858[];
extern u8 D_8006F86C[];
extern u8 D_8006F87C[];
extern void func_8002DAE8(void *);
extern Shape_8002F810 *func_8002E8C0(u16);
extern void func_8002F52C(Obj_8002F810 *);
extern void func_8002F730(void *, s32, SV_8002F810 *, u8 *);
extern s32 func_80032C28(s32, s32);
extern s32 func_80032E94(s32 *);
extern void func_80033428(s32 *, s16);

void func_8002F810(Obj_8002F810 *obj) {
    s32 pos[3];
    s32 xz[2];
    s32 t[3];
    Shape_8002F810 *e;
    s32 nv;
    s32 ns;
    s32 i;

    e = func_8002E8C0(obj->id);
    switch (e->type) {
    case 1:
    {
        Sub_8002F810 *sub = &e->s;
        sub->y = func_80032C28(e->s.r, e->s.r);
        nv = 8;
        obj->unk2C = func_80032C28(e->s.r, obj->x);
        func_8002F730(obj->sub, 5, obj->v, D_8006F87C);
        obj->v[0].vx = -(e->s.r >> 16);
        obj->v[3].vx = -(e->s.r >> 16);
        obj->v[4].vx = -(e->s.r >> 16);
        obj->v[7].vx = -(e->s.r >> 16);
        obj->v[1].vx = e->s.r >> 16;
        obj->v[2].vx = e->s.r >> 16;
        obj->v[5].vx = e->s.r >> 16;
        obj->v[6].vx = e->s.r >> 16;
        obj->v[0].vy = -(sub->x >> 16);
        obj->v[1].vy = -(sub->x >> 16);
        obj->v[4].vy = -(sub->x >> 16);
        obj->v[5].vy = -(sub->x >> 16);
        obj->v[2].vy = 0;
        obj->v[3].vy = 0;
        obj->v[6].vy = 0;
        obj->v[7].vy = 0;
        obj->v[0].vz = -(e->s.r >> 16);
        obj->v[1].vz = -(e->s.r >> 16);
        obj->v[2].vz = -(e->s.r >> 16);
        obj->v[3].vz = -(e->s.r >> 16);
        obj->v[4].vz = e->s.r >> 16;
        obj->v[5].vz = e->s.r >> 16;
        obj->v[6].vz = e->s.r >> 16;
        ns = 5;
        obj->v[7].vz = e->s.r >> 16;
        break;
    }
    case 2:
    {
        Sub_8002F810 *sub = &e->s;
        xz[0] = func_80032C28(e->s.r, obj->x);
        nv = 8;
        xz[1] = func_80032C28(sub->y, obj->z);
        obj->unk2C = func_80032E94(xz);
        func_8002F730(obj->sub, 5, obj->v, D_8006F858);
        obj->v[4].vx = -(e->s.r >> 16);
        obj->v[5].vx = -(e->s.r >> 16);
        obj->v[6].vx = -(e->s.r >> 16);
        obj->v[7].vx = -(e->s.r >> 16);
        obj->v[0].vx = e->s.r >> 16;
        obj->v[1].vx = e->s.r >> 16;
        obj->v[2].vx = e->s.r >> 16;
        obj->v[3].vx = e->s.r >> 16;
        obj->v[0].vy = -((sub->x + sub->z) >> 16);
        obj->v[1].vy = -((sub->x + sub->z) >> 16);
        obj->v[4].vy = -((sub->x - sub->z) >> 16);
        obj->v[5].vy = -((sub->x - sub->z) >> 16);
        obj->v[2].vy = -(sub->z >> 16);
        obj->v[3].vy = -(sub->z >> 16);
        obj->v[6].vy = -(-sub->z >> 16);
        obj->v[7].vy = -(-sub->z >> 16);
        obj->v[0].vz = -(sub->y >> 16);
        obj->v[3].vz = -(sub->y >> 16);
        obj->v[4].vz = -(sub->y >> 16);
        obj->v[7].vz = -(sub->y >> 16);
        obj->v[1].vz = sub->y >> 16;
        obj->v[2].vz = sub->y >> 16;
        obj->v[5].vz = sub->y >> 16;
        ns = 5;
        obj->v[6].vz = sub->y >> 16;
        break;
    }
    case 3:
    {
        Sub_8002F810 *sub = &e->s;
        xz[0] = func_80032C28(e->s.r, obj->x);
        nv = 6;
        xz[1] = func_80032C28(sub->y, obj->z);
        obj->unk2C = func_80032E94(xz);
        func_8002F730(obj->sub, 4, obj->v, D_8006F86C);
        obj->v[3].vx = -(e->s.r >> 16);
        obj->v[4].vx = -(e->s.r >> 16);
        obj->v[5].vx = -(e->s.r >> 16);
        obj->v[0].vx = e->s.r >> 16;
        obj->v[1].vx = e->s.r >> 16;
        obj->v[2].vx = e->s.r >> 16;
        obj->v[0].vy = -(sub->x >> 16);
        obj->v[1].vy = 0;
        obj->v[2].vy = 0;
        obj->v[3].vy = -((sub->x + sub->z * 2) >> 16);
        obj->v[5].vy = -((sub->z * 2) >> 16);
        obj->v[4].vy = -((sub->z * 2) >> 16);
        obj->v[2].vz = -(sub->y >> 16);
        obj->v[5].vz = -(sub->y >> 16);
        obj->v[1].vz = sub->y >> 16;
        obj->v[4].vz = sub->y >> 16;
        ns = 4;
        obj->v[0].vz = 0;
        obj->v[3].vz = 0;
        break;
    }
    case 0:
    {
        Sub_8002F810 *sub = &e->s;
        xz[0] = func_80032C28(sub->r, obj->x);
        nv = 0;
        xz[1] = func_80032C28(sub->y, obj->z);
        ns = nv;
        obj->unk2C = func_80032E94(xz);
        *(s32 *) obj |= 0x400000;
        break;
    }
    default:
        nv = 0;
        ns = nv;
        break;
    }
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    for (i = 0; i < nv; i++) {
        t[0] = func_80032C28(obj->v[i].vx << 16, pos[0]);
        t[1] = func_80032C28(obj->v[i].vy << 16, pos[1]);
        t[2] = func_80032C28(obj->v[i].vz << 16, pos[2]);
        func_80033428(t, -obj->rot);
        obj->v[i].vx = obj->px + (t[0] >> 16);
        obj->v[i].vy = obj->py + (t[1] >> 16);
        obj->v[i].vz = obj->pz + (t[2] >> 16);
    }
    for (i = 0; i < ns; i++) {
        func_8002DAE8(obj->sub[i]);
    }
    func_8002F52C(obj);
}
