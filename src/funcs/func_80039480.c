#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 off;
    u16 w;
    u16 h;
    u8 loaded;
    u8 r;
    u8 g;
    u8 b;
    s32 pal;
} Tex_80039480;

typedef struct {
    u8 pad0[3];
    u8 len;
} Hdr_80039480;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 w;
    s16 h;
} Sprt_80039480;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect_80039480;

typedef struct {
    u16 x;
    u16 y;
    u16 pad[2];
} Clut_80039480;

extern Sprt_80039480 *func_80039FF4(u32 *, Sprt_80039480 *, u16);
extern Sprt_80039480 *func_8003A1B8(u32 *, Sprt_80039480 *, u16 *, s32, s32, s32);
extern void func_8003A2E4(u8 *, u8 *, u8 *);
extern void func_8003AE98(Rect_80039480 *, u8 *, s32);
extern u32 func_8004683C(u16, u16, u32);
extern void func_8004966C(s16 *, s16 *, s16 *, u16, u16);
extern s32 D_8008A694;
extern u32 *D_8008B1A0;
extern u16 D_8008B1A4;
extern Sprt_80039480 *D_8008B3B0[2];
extern Clut_80039480 D_800A8404[];

#define getTPage_(tp, abr, x, y) \
    ((((tp) & 3) << 7) | (((abr) & 3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3FF) >> 6) | \
     (((y) & 0x200) << 2))

void func_80039480(Tex_80039480 *t, u8 *uv, u8 flags, s32 arg4, s32 arg5, s32 x, s32 y, u16 depth,
                   u16 clutBase) {
    s32 div;
    s32 tp;
    s32 mask;
    u16 *pal;
    Sprt_80039480 *p;
    Rect_80039480 rect;
    s16 cr;
    s16 cg;
    s16 cb;
    u32 v;
    u16 semi;
    s32 hi;
    u8 c;
    u32 *ot;
    s16 u0;
    s32 v0;
    s32 w;
    s32 h;

    if (depth == 4) {
        div = 4;
        tp = 0;
        mask = 0xFF;
    } else if (depth == 8) {
        div = 2;
        tp = 1;
        mask = 0x7F;
    } else {
        div = 1;
        tp = 2;
        mask = 0x3F;
    }
    pal = NULL;
    if (t->pal != 0) {
        pal = (u16 *) ((u8 *) t + t->pal);
    }
    p = D_8008B3B0[-1];
    if (t->loaded == 0) {
        cr = 0xFF;
        cg = 0xFF;
        cb = 0xFF;
        func_8004966C(&cr, &cg, &cb, ((t->w + div - 1) / div) * 2, t->h);
        t->r = cr;
        t->g = cg;
        t->b = cb;
    }
    v = func_8004683C(t->r, t->g, t->b);
    rect.x = v;
    rect.y = v >> 16;
    rect.w = t->w / div;
    rect.h = t->h;
    if (t->loaded == 0) {
        t->loaded = 1;
        func_8003AE98(&rect, (u8 *) t + t->off, 1);
    }
    u0 = (t->g << ((div >> 1) - 1)) & mask;
    u0 += uv[0];
    v0 = uv[1] + t->b;
    w = uv[2];
    h = uv[3];
    v0 += func_8004683C(t->r, 0, 0) >> 16;
    ((Hdr_80039480 *) p)->len = 4;
    p->code = 0x64;
    p->r0 = 0x80;
    p->g0 = 0x80;
    p->b0 = 0x80;
    p->x0 = x;
    p->y0 = y + 0x78;
    p->w = w;
    p->h = h;
    p->u0 = u0;
    p->v0 = v0;
    flags &= 0xFF;
    switch (flags) {
    case 1:
        semi = 1;
        hi = 0;
        break;
    case 2:
        semi = 0;
        hi = 1;
        break;
    case 3:
        semi = 0;
        hi = 1;
        break;
    default:
        semi = 0;
        hi = 0;
        break;
    }
    if (semi) {
        p->code |= 2;
    } else {
        p->code &= ~2;
    }
    if (pal != NULL) {
        c = (*pal >> (hi * 8)) & 0xFF;
        p->clut = clutBase + ((D_800A8404[c].y << 6) | ((D_800A8404[c].x >> 4) & 0x3F));
    }
    ot = D_8008B1A0;
    p->tag = (p->tag & 0xFF000000) | (*ot & 0xFFFFFF);
    *ot = (*ot & 0xFF000000) | ((u32) p & 0xFFFFFF);
    p++;
    if (pal != NULL) {
        p = func_8003A1B8(ot, p, pal, flags, arg4, arg5);
    }
    if (D_8008B1A4 != getTPage_(tp, 0, rect.x, rect.y)) {
        p = func_80039FF4(D_8008B1A0, p, getTPage_(tp, 0, rect.x, rect.y));
    }
    D_8008B3B0[-1] = p;
    D_8008B1A0--;
}
