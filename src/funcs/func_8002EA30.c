#include "common.h"

typedef struct {
    u8 pad0[4];
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
} Sub_8002EA30;

typedef struct {
    u8 *f0;
    u8 pad04[0x18];
    Sub_8002EA30 *f1C;
    s16 h20;
    s16 h22;
    s16 h24;
    u32 f28;
    u8 *f2C;
} Src_8002EA30;

typedef struct {
    u32 state;
    u8 pad04[4];
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1C;
    u32 f20;
    u32 f24;
    u32 f28;
    u8 *f2C;
    u32 f30;
    u32 f34;
    u16 f38;
    u8 pad3A[2];
    u32 f3C;
    u32 f40;
} Out_8002EA30;

extern Src_8002EA30 *func_8002CB8C(u32 a0, u32 a1);
extern u32 func_8002C490(u8 *a0);

s32 func_8002EA30(u32 a0, u32 a1, Out_8002EA30 *o) {
    Src_8002EA30 *s;
    u8 *sub;

    memset(o, 0, 0x44);
    s = func_8002CB8C(a0, a1);
    if (s == NULL) {
        return 0;
    }
    o->f8 = (s32) s->h20 << 16;
    o->fC = (s32) s->h22 << 16;
    o->f10 = (s32) s->h24 << 16;
    o->f14 = s->f28;
    o->f18 = s->f1C->f4;
    o->f1C = s->f1C->f8;
    o->f20 = s->f1C->fC;
    o->f24 = s->f1C->f10;
    if (s->f2C == NULL) {
        o->state = 1;
        o->f28 = *(u16 *) (*(u8 **) ((u8 *) s->f0 + 0x2C) + 2);
        sub = (u8 *) s->f1C;
        o->f2C = sub;
        o->f34 = func_8002C490(sub);
        o->f30 = *(u32 *) ((u8 *) s->f0 + 0x2C);
        return 1;
    }
    o->state = 2;
    o->f3C = (u32) s->f2C;
    o->f38 = *(u16 *) s->f2C;
    o->f40 = 0;
    return 1;
}
