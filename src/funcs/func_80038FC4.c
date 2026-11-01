#include "common.h"

typedef struct {
    u16 w;
    u16 h;
    s32 off;
    u8 pad8[4];
    u8 loaded;
    u8 r;
    u8 g;
    u8 b;
} Tex_80038FC4;

typedef struct {
    u8 pad0[3];
    u8 len;
} Hdr_80038FC4;

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
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad1E;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad26;
} PolyFT4_80038FC4;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect_80038FC4;

typedef struct {
    u16 x;
    u16 y;
    u16 pad[2];
} Clut_80038FC4;

#define setXYWH_(p, _x0, _y0, _w, _h) \
    (p)->x0 = (_x0), (p)->y0 = (_y0), (p)->x1 = (_x0) + (_w), (p)->y1 = (_y0), (p)->x2 = (_x0), \
    (p)->y2 = (_y0) + (_h), (p)->x3 = (_x0) + (_w), (p)->y3 = (_y0) + (_h)
#define setUVWH_(p, _u0, _v0, _w, _h) \
    (p)->u0 = (_u0), (p)->v0 = (_v0), (p)->u1 = (_u0) + (_w), (p)->v1 = (_v0), (p)->u2 = (_u0), \
    (p)->v2 = (_v0) + (_h), (p)->u3 = (_u0) + (_w), (p)->v3 = (_v0) + (_h)

extern void func_8003A054(u16);
extern PolyFT4_80038FC4 *func_8003A1B8(u32 *, PolyFT4_80038FC4 *, u16 *, s32, s32, s32);
extern void func_8003A2E4(u8 *, u8 *, u8 *);
extern void func_8003AE98(Rect_80038FC4 *, u8 *, s32);
extern u32 func_8004683C(u16, u16, u32);
extern void func_8004966C(s16 *, s16 *, s16 *, u16, u16);
extern s32 D_8008A694;
extern u32 *D_8008B1A0;
/* D_8008B3AC accessed as D_8008B3B0[-1]: small (<=8 byte) decl makes gcc emit a
   macro access; sym-N is never gp-relative under maspsx, giving the game's lui/lw. */
extern PolyFT4_80038FC4 *D_8008B3B0[2];
extern Clut_80038FC4 D_800A8404[];

void func_80038FC4(u8 *base, u16 idx, u16 *pal, u8 flags, s32 arg4, s32 arg5, s32 abr, s32 x,
                   s32 y, s32 w, s32 h, s32 sx, s32 sy, u16 depth, u16 clutBase) {
    s32 div;
    s32 mask;
    Tex_80038FC4 *t;
    PolyFT4_80038FC4 *p;
    Rect_80038FC4 rect;
    s16 cr;
    s16 cg;
    s16 cb;
    u8 r;
    u8 g;
    u8 b;
    u32 v;
    u32 vb;
    u16 semi;
    s32 hi;
    s32 c;
    s16 x1;
    s16 y0;
    s16 y2;
    u32 *ot;
    u8 u0;
    u8 v0;
    u8 u1;
    u8 v2;

    if (depth == 4) {
        div = 4;
        mask = 0xFF;
    } else if (depth == 8) {
        div = 2;
        mask = 0x7F;
    } else {
        div = 1;
        mask = 0x3F;
    }
    t = (Tex_80038FC4 *) (base + (idx * 16 + 0x14));
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
        func_8003AE98(&rect, base + t->off, 1);
    }
    ((Hdr_80038FC4 *) p)->len = 9;
    p->code = 0x2C;
    p->r0 = 0x80;
    p->g0 = 0x80;
    p->b0 = 0x80;
    y0 = y + 0x78;
    setXYWH_(p, x, y0, (w * sx - 0x9000) >> 16, (h * sy - 0x9000) >> 16);
    vb = func_8004683C(t->r, 0, 0) >> 16;
    u0 = (t->g << ((div >> 1) - 1)) & mask;
    v0 = t->b + vb;
    setUVWH_(p, u0, v0, w - 1, h - 1);
    flags &= 7;
    p->tpage = (1 << 7) | ((abr & 3) << 5) | ((rect.y & 0x100) >> 4) | ((rect.x & 0x3FF) >> 6) |
               ((rect.y & 0x200) << 2);
    func_8003A054(p->tpage);
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
        if (D_8008A694 != 0) {
            Clut_80038FC4 *e;

            func_8003A2E4(&r, &g, &b);
            p->r0 = r;
            p->g0 = g;
            p->b0 = b;
            e = &D_800A8404[c];
            p->clut = clutBase + ((e->y << 6) | ((e->x >> 4) & 0x3F));
        } else {
            Clut_80038FC4 *tb = D_800A8404;
            Clut_80038FC4 *e = &tb[c];
            p->clut = clutBase + ((e->y << 6) | ((e->x >> 4) & 0x3F));
        }
    }
    ot = D_8008B1A0;
    p->tag = (p->tag & 0xFF000000) | (*ot & 0xFFFFFF);
    *ot = (*ot & 0xFF000000) | ((u32) p & 0xFFFFFF);
    p++;
    if (pal != NULL) {
        p = func_8003A1B8(ot, p, pal, flags, arg4, arg5);
    }
    D_8008B3B0[-1] = p;
    D_8008B1A0--;
}
