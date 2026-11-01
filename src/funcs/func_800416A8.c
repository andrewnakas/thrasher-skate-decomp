#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
} Vec_800416A8;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0xA];
} Vert_800416A8;

typedef struct {
    u16 flags;
    u8 size;
    u8 type;
    u8 pad4[0x1C];
    u8 uv[6];
    u16 idx3;
    u16 idx4;
} Prim_800416A8;

typedef struct {
    u8 pad0[2];
    u16 nprim;
    u8 pad4[6];
    u16 fA;
    u8 padC[6];
    u8 f12;
    u8 f13;
    s16 f14;
    s16 f16;
    s16 f18;
    u8 nvert;
    u8 pad1B[0xD];
    Prim_800416A8 *prims;
    Vert_800416A8 *verts;
} Obj_800416A8;

typedef struct {
    u16 flags;
    u8 pad2[0xE];
} Tex_800416A8;

typedef struct {
    u8 pad0[0x30];
    s32 ntex;
} Ctx_800416A8;

extern void func_8004126C(Obj_800416A8 *, Prim_800416A8 *, s32);
extern s16 func_80047420(u16);
extern u8 func_80047460(u16);
extern s16 func_800476C8(u16);
extern s16 func_8004774C(u16);
extern s32 D_8008B344;
extern volatile s32 D_8008B348;
extern Ctx_800416A8 *D_8008B34C;
extern s32 D_8008B354;
extern s32 D_8008B364[2];
extern Vec_800416A8 D_8008A7A8;
extern Vec_800416A8 D_8008A7B4;
extern Tex_800416A8 D_800AB794[];

#define CLAMP_U(k)                                         \
    if (tex[k] >= func_800476C8(D_8008B344 + idx)) {       \
        tex[k] = func_800476C8(D_8008B344 + idx) - 1;      \
    }
#define CLAMP_V(k)                                         \
    if (tex[k] >= func_8004774C(D_8008B344 + idx)) {       \
        tex[k] = func_8004774C(D_8008B344 + idx) - 1;      \
    }
#define ADD_U(k) tex[k] += (func_80047420(D_8008B344 + idx) * mult) & mask
#define ADD_V(k) tex[k] += func_80047460(D_8008B344 + idx)

void func_800416A8(Obj_800416A8 *obj) {
    Vec_800416A8 mn;
    Vec_800416A8 mx;
    Vert_800416A8 *v;
    Prim_800416A8 *p;
    u8 *tex;
    u16 idx;
    s32 mask;
    s32 mult;
    s32 t;
    s32 u;
    s16 n;
    u16 i;

    if (D_8008B348 & 4) {
        mn = D_8008A7A8;
        mx = D_8008A7B4;
        v = obj->verts;
        for (i = 0; i < obj->nvert; i++, v++) {
            t = v->x;
            if (mn.vx < t) {
                t = mn.vx;
            }
            mn.vx = t;
            t = v->y;
            if (mn.vy < t) {
                t = mn.vy;
            }
            mn.vy = t;
            t = v->z;
            if (mn.vz < t) {
                t = mn.vz;
            }
            mn.vz = t;
            t = v->x;
            if (t < mx.vx) {
                t = mx.vx;
            }
            mx.vx = t;
            t = v->y;
            if (t < mx.vy) {
                t = mx.vy;
            }
            mx.vy = t;
            u = v->z;
            if (u < mx.vz) {
                u = mx.vz;
            }
            mx.vz = u;
        }
        obj->f14 = (mx.vx - mn.vx) >> 1;
        obj->f16 = (mx.vy - mn.vy) >> 1;
        obj->f18 = (mx.vz - mn.vz) >> 1;
    }
    p = obj->prims;
    for (i = 0; i < obj->nprim; i++) {
        if (D_8008B348 & 4) {
            if (p->flags & 1) {
                if (D_8008B354 != 0) {
                    func_8004126C(obj, p, D_8008B364[D_8008B354 - 1]);
                } else {
                    func_8004126C(obj, p, 0);
                }
                if (p->flags & 0x100) {
                    obj->f12++;
                } else {
                    obj->f13++;
                }
            } else {
                obj->fA++;
            }
        }
        if (D_8008B348 & 2) {
            switch (p->type) {
            case 3:
                n = p->idx4;
                break;
            case 2:
            case 6:
                n = p->idx3;
                break;
            default:
                n = -1;
                break;
            }
            if (D_8008B34C->ntex < n + 1) {
                D_8008B34C->ntex = n + 1;
            }
        }
        if (D_8008B348 & 0x10) {
            if (D_8008B348 & 0x10) {
                switch (p->type) {
                case 2:
                    tex = p->uv;
                    if (!(p->flags & 0x800)) {
                        idx = *(u16 *) (tex + 6);
                        t = D_800AB794[idx + D_8008B344].flags & 0x180;
                        if (t == 0) {
                            mask = 0xFF;
                            mult = 4;
                        } else if (t == 0x80) {
                            mask = 0x7F;
                            mult = 2;
                        } else {
                            mask = 0x3F;
                            mult = 1;
                        }
                        CLAMP_U(0);
                        CLAMP_U(2);
                        CLAMP_U(4);
                        CLAMP_V(1);
                        CLAMP_V(3);
                        CLAMP_V(5);
                        if (!(p->flags & 0x80)) {
                            ADD_U(0);
                            ADD_U(2);
                            ADD_U(4);
                            ADD_V(1);
                            ADD_V(3);
                            ADD_V(5);
                        }
                    }
                    *(u16 *) (tex + 6) <<= 1;
                    break;
                case 3:
                    tex = p->uv;
                    if (!(p->flags & 0x800)) {
                        idx = *(u16 *) (tex + 8);
                        t = D_800AB794[idx + D_8008B344].flags & 0x180;
                        if (t == 0) {
                            mask = 0xFF;
                            mult = 4;
                        } else if (t == 0x80) {
                            mask = 0x7F;
                            mult = 2;
                        } else {
                            mask = 0x3F;
                            mult = 1;
                        }
                        CLAMP_U(0);
                        CLAMP_U(2);
                        CLAMP_U(4);
                        CLAMP_U(6);
                        CLAMP_V(1);
                        CLAMP_V(3);
                        CLAMP_V(5);
                        CLAMP_V(7);
                        if (!(p->flags & 0x80)) {
                            ADD_U(0);
                            ADD_U(2);
                            ADD_U(4);
                            ADD_U(6);
                            ADD_V(1);
                            ADD_V(3);
                            ADD_V(5);
                            ADD_V(7);
                        }
                    }
                    *(u16 *) (tex + 8) <<= 1;
                    break;
                case 6:
                    tex = p->uv;
                    if (!(p->flags & 0x800)) {
                        idx = *(u16 *) (tex + 6);
                        t = D_800AB794[idx + D_8008B344].flags & 0x180;
                        if (t == 0) {
                            mask = 0xFF;
                            mult = 4;
                        } else if (t == 0x80) {
                            mask = 0x7F;
                            mult = 2;
                        } else {
                            mask = 0x3F;
                            mult = 1;
                        }
                        CLAMP_U(0);
                        CLAMP_U(2);
                        CLAMP_U(4);
                        CLAMP_V(1);
                        CLAMP_V(3);
                        CLAMP_V(5);
                        if (!(p->flags & 0x80)) {
                            ADD_U(0);
                            ADD_U(2);
                            ADD_U(4);
                            ADD_V(1);
                            ADD_V(3);
                            ADD_V(5);
                        }
                    }
                    *(u16 *) (tex + 6) <<= 1;
                    break;
                case 0:
                case 1:
                case 4:
                case 5:
                    break;
                }
            }
        }
        p = (Prim_800416A8 *) ((u8 *) p + p->size);
    }
}
