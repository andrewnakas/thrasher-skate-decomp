#include "common.h"

typedef struct {
    u16 x, y, w, h;
} Rect_8003BA14;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} PolyF4_8003BA14;

typedef struct {
    Rect_8003BA14 r;
    u8 pad[0x10];
} Env_8003BA14;

extern s32 D_8008A70C;
extern s32 D_8008A754;
extern Rect_8003BA14 D_800824A4[];
extern u8 D_800A9404[];
extern s32 D_8008B1DC[2];

extern void func_8005A760(Env_8003BA14 *);
extern void func_8005A814(void *, Rect_8003BA14 *, s32);
extern void func_8005A0A8(void *);
extern void func_80059CF0(s32);

void func_8003BA14(void) {
    Env_8003BA14 env;
    PolyF4_8003BA14 *p;
    s16 x;
    s32 l;
    s32 t;
    s32 h;

    if (D_8008A70C != 0) {
        l = 0xFD;
        t = 0x17A;
        x = D_8008A754 / 8;
        func_8005A760(&env);
        D_800824A4[0].x = env.r.x;
        D_800824A4[0].y = env.r.y;
        D_800824A4[0].w = env.r.w;
        D_800824A4[0].h = h = env.r.h;
        func_8005A814(D_800A9404, D_800824A4, h);
        func_8005A0A8(D_800A9404);
        p = (PolyF4_8003BA14 *)D_8008B1DC;
        ((u8 *)&p->tag)[3] = 5;
        p->code = 0x28;
        x += l;
        p->r0 = 0x40;
        p->g0 = 0x40;
        p->b0 = 0x40;
        p->x0 = l;
        p->y0 = t;
        p->x1 = x;
        p->y1 = t;
        p->x2 = l;
        p->y2 = 0x192;
        p->x3 = x;
        p->y3 = 0x192;
        func_8005A0A8(p);
        func_80059CF0(1);
    }
}
