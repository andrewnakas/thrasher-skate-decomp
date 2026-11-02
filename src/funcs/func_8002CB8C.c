/* a4 r5: gp globals as one-field structs (in-struct MEMs keep the struct stores ahead of them), pos via one temp, first==c test nested. */
#include "common.h"

typedef struct {
    u16 fx;
    s16 x;
    u16 fy;
    s16 y;
    u16 fz;
    s16 z;
} V3;

typedef struct {
    u8 pad0[3];
    u8 f3;
} Obj;

typedef struct {
    s32 f0;
    s16 x0;
    s16 y0;
    s16 z0;
    s16 x1;
    s16 y1;
    s16 z1;
    s32 dx;
    s32 dy;
    s32 dz;
    Obj *f1C;
    s16 hx;
    s16 hy;
    s16 hz;
    s16 pad26;
    u8 f28[4];
    s32 f2C;
} Hit;

typedef struct {
    u8 pad0[0x28];
    s32 f28;
} Cell;

extern Hit D_800A1C50;
extern u8 D_800A1E00[];
extern struct { s16 v; } D_8008AFC4;
extern struct { s16 v; } D_8008AFC6;
extern struct { s16 v; } D_8008AFC8;
extern struct { s16 v; } D_8008AFCC;
extern struct { s16 v; } D_8008AFCE;
extern struct { s16 v; } D_8008AFD0;
extern struct { s32 v; } D_8008AFB4;
extern struct { s32 v; } D_8008AFB8;
extern struct { s32 v; } D_8008AFBC;
extern u8 *D_8008B04C;
extern s32 D_8008B050;

Cell *func_8002C0B8(s16 *);
void func_8002CE0C(s32);
s32 func_8002D038(Cell *);
s32 func_8002D904(Cell *);
s32 func_8002D56C(Cell *, s16 *, s16 *);
void func_8002D198(u8 *, s32 *, u8 *);
s32 func_8002DD88(Obj *, s32);

Hit *func_8002CB8C(V3 *a, V3 *b) {
    s16 pos[3];
    s32 out[3];
    Cell *first;
    Cell *end;
    Cell *c;
    s32 x0, y0, z0, x1, y1, z1;
    s32 dx, dy, dz;
    s32 t;

    x0 = a->x;
    D_800A1C50.x0 = x0;
    y0 = a->y;
    D_800A1C50.y0 = y0;
    z0 = a->z;
    D_800A1C50.z0 = z0;
    x1 = b->x;
    D_800A1C50.x1 = x1;
    y1 = b->y;
    D_800A1C50.y1 = y1;
    z1 = b->z;
    D_800A1C50.z1 = z1;
    dx = x1 - x0;
    D_800A1C50.dx = dx;
    dy = y1 - y0;
    D_800A1C50.dy = dy;
    dz = z1 - z0;
    D_800A1C50.dz = dz;
    D_800A1C50.hx = x1;
    D_800A1C50.hy = y1;
    D_800A1C50.hz = z1;
    D_800A1C50.f0 = 0;
    D_800A1C50.f2C = 0;
    D_8008AFC4.v = x0;
    D_8008AFC6.v = y0;
    D_8008AFC8.v = z0;
    D_8008AFCC.v = x1;
    D_8008AFCE.v = y1;
    D_8008AFD0.v = z1;
    D_8008AFB4.v = dx;
    D_8008AFB8.v = dy;
    D_8008AFBC.v = dz;
    first = NULL;
    end = func_8002C0B8(&D_8008AFCC.v);
    t = a->x;
    pos[0] = t;
    t = a->y;
    pos[1] = t;
    t = a->z;
    pos[2] = t;
    while (1) {
        c = func_8002C0B8(pos);
        if (c == NULL) {
            break;
        }
        if (first != NULL) {
            if (first == c) {
                break;
            }
        } else {
            first = c;
        }
        D_8008B04C = D_800A1E00;
        D_8008B050 = 0;
        func_8002CE0C(c->f28);
        if (func_8002D038(c) != 0) {
            func_8002D904(c);
            goto hit;
        }
        if (func_8002D904(c) != 0) {
            goto hit;
        }
        if (c == end) {
            break;
        }
        if (func_8002D56C(c, pos, &D_8008AFCC.v) == 0) {
            break;
        }
    }
    return NULL;
hit:
    D_8008AFC4.v = D_800A1C50.x0;
    D_8008AFC6.v = D_800A1C50.y0;
    D_8008AFC8.v = D_800A1C50.z0;
    D_8008AFCC.v = D_800A1C50.x1;
    D_8008AFCE.v = D_800A1C50.y1;
    D_8008AFD0.v = D_800A1C50.z1;
    D_8008AFB4.v = D_8008AFCC.v - D_8008AFC4.v;
    D_8008AFB8.v = D_8008AFCE.v - D_8008AFC6.v;
    D_8008AFBC.v = D_8008AFD0.v - D_8008AFC8.v;
    func_8002D198((u8 *) D_800A1C50.f1C + 4, out, D_800A1C50.f28);
    D_800A1C50.hx = (out[0] + 0x8000) >> 16;
    D_800A1C50.hy = (out[1] + 0x8000) >> 16;
    D_800A1C50.hz = (out[2] + 0x8000) >> 16;
    if (D_800A1C50.f1C->f3 != 0 && func_8002DD88(D_800A1C50.f1C, 0) != 0) {
        return NULL;
    }
    return &D_800A1C50;
}
