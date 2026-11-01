#include "common.h"

typedef struct {
    u8 pad0[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1E;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad26;
    u8 f28;
    u8 f29;
    u8 pad2A[6];
} Rec;

typedef struct {
    u16 tpage;
    u16 clut;
    u8 u0, v0, u1, v1;
    u8 pad8[4];
    u8 w, h;
    u8 padE[2];
} Tex;

extern Tex D_800AB794[];
extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

u32 func_80020D74(u8, s32);
s32 func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

u32 func_8002103C(u8 a0, u16 tex, s16 x, s16 y, u8 semi) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    Tex *t;
    Rec *p;
    u32 id;
    u32 i;
    u32 k;
    u8 flag;

    id = func_80020D74(a0, 0);
    flag = semi;
    if (id == -1) {
        return id;
    }
    t = &D_800AB794[tex];
    func_80020C34((id >> 16) & 0xFF, (id & 0xFF00) >> 8, D_8008A2AC, &sp18, &sp1C, &sp20);
    p = (Rec *) (sp18 + (id & 0xFF) * 0x30);
    p->len = 9;
    p->code = 0x2C;
    p->r0 = 0xFF;
    p->g0 = 0xFF;
    p->b0 = 0xFF;
    p->clut = t->clut;
    p->tpage = t->tpage;
    if (flag) {
        p->code |= 2;
    }
    p->x0 = x;
    p->y0 = y;
    p->u0 = t->u0;
    p->v0 = t->v0;
    p->x1 = t->w + x;
    p->y1 = y;
    p->u1 = t->u1;
    p->v1 = t->v0;
    p->x2 = x;
    p->y2 = t->h + y;
    p->u2 = t->u0;
    p->v2 = t->v1;
    p->x3 = t->w + x;
    p->y3 = t->h + y;
    p->u3 = t->u1;
    p->v3 = t->v1;
    ((Rec *) (sp18 + (id & 0xFF) * 0x30))->f28 = 2;
    ((Rec *) (sp18 + (id & 0xFF) * 0x30))->f29 = semi;
    D_8009C0A4[D_8008A2A4++] = id;
    for (i = 0; i < D_8008A2A8; i++) {
        if (D_8009C6D4[i] == id) {
            D_8008A2A8 -= 1;
            for (k = i; k < D_8008A2A8; k++) {
                D_8009C6D4[k] = D_8009C6D4[k + 1];
            }
        }
    }
    return id;
}
