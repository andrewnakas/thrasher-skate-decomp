#include "common.h"

typedef struct {
    s32 vx;
    s32 vy;
    s32 vz;
    s32 pad;
} Vec;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3;

typedef struct {
    u16 active;
    u16 flags;
    u8 pad4[0x34 - 0x4];
    s32 f34;
    s32 f38;
    u8 pad3C[0x44 - 0x3C];
    V3 pos;
    V3 old;
    V3 tmp;
    V3 vel;
    u8 pad74[0x8C - 0x74];
} Body;

typedef struct {
    s32 type;
    u8 pad4[0x1C];
} Cons;

typedef struct World World;
struct World {
    u32 count;
    Body bodies[20];
    u32 ncons;
    Cons cons[65];
    u8 pad1318[4];
    V3 vel;
    void (*cb)(World *, u32, Vec *, Vec *, s32, s32);
};

void func_80022F24(World *);
s32 func_80023B1C(Body *, Vec *, Vec *, s32 *, s32 *);
void func_80023BB4(Cons *);
void func_80023D2C(Cons *);
void func_80023EC4(Cons *);
s32 func_80032C28(s32, s32);
s32 func_80032C54(s32, s32);
void func_80032FE0(Vec *);
void func_80032FF4(V3 *, Vec *);
void func_800331FC(void *, s32);

void func_80023004(World *w) {
    Vec a;
    Vec b;
    Vec acc;
    s32 c;
    s32 d;
    u32 i;
    u32 pass;
    s32 total;
    void (*cb)(World *, u32, Vec *, Vec *, s32, s32);

    for (i = 0; i < w->count; i++) {
        w->bodies[i].old.x = w->bodies[i].pos.x;
        w->bodies[i].old.y = w->bodies[i].pos.y;
        w->bodies[i].old.z = w->bodies[i].pos.z;
        if (w->bodies[i].active != 0 && func_80023B1C(&w->bodies[i], &a, &b, &c, &d) != 0) {
            cb = w->cb;
            if (cb != NULL) {
                cb(w, i, &a, &b, c, d);
            }
        }
        w->bodies[i].pos.x -= w->vel.x;
        w->bodies[i].pos.y -= w->vel.y;
        w->bodies[i].pos.z -= w->vel.z;
    }
    func_80022F24(w);
    for (pass = 0; pass < 2; pass++) {
        for (i = 0; i < w->count; i++) {
                w->bodies[i].tmp.x = w->bodies[i].pos.x;
            w->bodies[i].tmp.y = w->bodies[i].pos.y;
            w->bodies[i].tmp.z = w->bodies[i].pos.z;
            func_800331FC(&w->bodies[i].tmp, w->bodies[i].f34);
            w->bodies[i].f38 = w->bodies[i].f34;
        }
        for (i = 0; i < w->ncons; i++) {
            switch ((u32) w->cons[i].type) {
            case 1:
                func_80023D2C(&w->cons[i]);
            case 0:
                func_80023BB4(&w->cons[i]);
                break;
            case 2:
                func_80023EC4(&w->cons[i]);
                break;
            }
        }
        for (i = 0; i < w->count; i++) {
                if (w->bodies[i].active != 0) {
                s32 s = func_80032C54(0x10000, w->bodies[i].f38);
                w->bodies[i].pos.x = w->bodies[i].tmp.x;
                w->bodies[i].pos.y = w->bodies[i].tmp.y;
                w->bodies[i].pos.z = w->bodies[i].tmp.z;
                func_800331FC(&w->bodies[i].pos, s);
                acc.vx += func_80032C28(w->bodies[i].pos.x, w->bodies[i].f34);
                acc.vy += func_80032C28(w->bodies[i].pos.y, w->bodies[i].f34);
                acc.vz += func_80032C28(w->bodies[i].pos.z, w->bodies[i].f34);
            }
        }
    }
    func_80032FE0(&acc);
    total = 0;
    for (i = 0; i < w->count; i++) {
        if (w->bodies[i].active != 0) {
            acc.vx += func_80032C28(w->bodies[i].pos.x, w->bodies[i].f34);
            acc.vy += func_80032C28(w->bodies[i].pos.y, w->bodies[i].f34);
            acc.vz += func_80032C28(w->bodies[i].pos.z, w->bodies[i].f34);
            w->bodies[i].pos.x += w->vel.x;
            w->bodies[i].pos.y += w->vel.y;
            total += w->bodies[i].f34;
            w->bodies[i].pos.z += w->vel.z;
        } else {
            w->bodies[i].pos.x = w->bodies[i].old.x;
            w->bodies[i].pos.y = w->bodies[i].old.y;
            w->bodies[i].pos.z = w->bodies[i].old.z;
        }
    }
    if (total > 0) {
        func_800331FC(&acc, func_80032C54(0x10000, total));
    }
    func_80032FF4(&w->vel, &acc);
    for (i = 0; i < w->count; i++) {
        if (!(w->bodies[i].flags & 1)) {
            w->bodies[i].vel.x = w->bodies[i].pos.x - w->bodies[i].old.x;
            w->bodies[i].vel.y = w->bodies[i].pos.y - w->bodies[i].old.y;
            w->bodies[i].vel.z = w->bodies[i].pos.z - w->bodies[i].old.z;
        }
    }
}
