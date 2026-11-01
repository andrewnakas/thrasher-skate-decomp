/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct PTag_800458F4 {
    u32 addr : 24;
    u32 len : 8;
} PTag_800458F4;

typedef struct Tex_800458F4 {
    u16 tpage;
    u16 clut;
    u8 u0;
    u8 v0;
    u8 u1;
    u8 v1;
    u8 pad8[8];
} Tex_800458F4;

typedef struct Params_800458F4 {
    s32 w;
    s32 h;
    s32 sx;
    s32 sy;
    s32 x1;
    s32 y1;
    u8 du0;
    u8 pad19[3];
    u8 dv0;
    u8 pad1D[3];
    u8 du1;
    u8 pad21[3];
    u8 dv1;
    u8 pad25[3];
} Params_800458F4;

typedef struct ParamsB_800458F4 {
    u8 pad0[0x20];
    s32 w;
    s32 h;
    s32 cluto;
    s32 depth;
    u8 du0;
    u8 dv0;
    u8 du1;
    u8 dv1;
} ParamsB_800458F4;

typedef struct PolyFT4_800458F4 {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} PolyFT4_800458F4;

typedef struct PolyF4_800458F4 {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} PolyF4_800458F4;

extern Tex_800458F4 D_800AB794[];
extern u8 D_8008B3A0[0x40];
extern u8 D_8008B3AC[0x40];
extern s16 func_800476A8(Tex_800458F4 *);
extern s16 func_8004772C(Tex_800458F4 *);

void func_800458F4(u32 arg0, s32 x, s32 y, u32 flags, Params_800458F4 *p) {
    u8 *prim;
    Tex_800458F4 *t;
    s32 cluto;
    s32 depth;
    s32 w;
    s32 h;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    prim = *(u8 **) D_8008B3AC;
    if (flags & 4) {
        t = &D_800AB794[arg0];
    } else {
        t = NULL;
    }
    cluto = 0;
    if (flags & 0x800) {
        cluto = ((ParamsB_800458F4 *) p)->cluto;
    }
    depth = 2;
    if (flags & 0x1000) {
        depth = ((ParamsB_800458F4 *) p)->depth;
    }
    if (flags & 0x200) {
        w = p->w;
        h = p->h;
    } else if (flags & 0x80) {
        w = p->x1 - x;
        h = p->y1 - y;
    } else if (flags & 4) {
        if (flags & 0x400) {
            w = ((ParamsB_800458F4 *) p)->w;
            h = ((ParamsB_800458F4 *) p)->h;
        } else {
            w = func_800476A8(t);
            h = func_8004772C(t);
        }
    } else {
        w = h = 0;
    }
    if (flags & 0x100) {
        w = (w * p->sx) >> 16;
        h = (h * p->sy) >> 16;
    }
    if (flags & 8) {
        x0 = x - (w >> 1);
    } else {
        x0 = x;
    }
    if (flags & 0x10) {
        y0 = y - (h >> 1);
    } else {
        y0 = y;
    }
    if (flags & 0x80) {
        x1 = p->x1;
        y1 = p->y1;
    } else {
        x1 = x0 + w;
        y1 = y0 + h;
    }
    if (flags & 0x20) {
        x0 -= w;
        x1 -= w;
    }
    if (flags & 0x40) {
        y0 -= h;
        y1 -= h;
    }
    if (prim != NULL) {
        if (flags & 4) {
            if (flags & 1) {
                x0 ^= x1;
                x1 ^= x0;
                x0 ^= x1;
            }
            if (flags & 2) {
                y0 ^= y1;
                y1 ^= y0;
                y0 ^= y1;
            }
            ((u8 *) &((PolyFT4_800458F4 *) prim)->tag)[3] = 9;
            ((u8 *) &((PolyFT4_800458F4 *) prim)->rgbc)[3] = 0x2C;
            ((PolyFT4_800458F4 *) prim)->clut = t->clut + cluto;
            ((PolyFT4_800458F4 *) prim)->tpage = t->tpage;
            ((PolyFT4_800458F4 *) prim)->rgbc = 0x2C808080;
            if (flags & 0x2000) {
                ((u8 *) &((PolyFT4_800458F4 *) prim)->rgbc)[3] |= 2;
            }
            ((PolyFT4_800458F4 *) prim)->x0 = x0;
            ((PolyFT4_800458F4 *) prim)->y0 = y0;
            ((PolyFT4_800458F4 *) prim)->x1 = x1;
            ((PolyFT4_800458F4 *) prim)->y1 = y0;
            ((PolyFT4_800458F4 *) prim)->x2 = x0;
            ((PolyFT4_800458F4 *) prim)->y2 = y1;
            ((PolyFT4_800458F4 *) prim)->x3 = x1;
            ((PolyFT4_800458F4 *) prim)->y3 = y1;
            if (flags & 0x400) {
                ((PolyFT4_800458F4 *) prim)->u0 = t->u0 + p->du0;
                ((PolyFT4_800458F4 *) prim)->v0 = t->v0 + p->dv0;
                ((PolyFT4_800458F4 *) prim)->u3 = ((PolyFT4_800458F4 *) prim)->u0 + p->du1;
                ((PolyFT4_800458F4 *) prim)->v3 = ((PolyFT4_800458F4 *) prim)->v0 + p->dv1;
            } else if (flags & 0x4000) {
                ((PolyFT4_800458F4 *) prim)->u0 = t->u0 + ((ParamsB_800458F4 *) p)->du0;
                ((PolyFT4_800458F4 *) prim)->v0 = t->v0 + ((ParamsB_800458F4 *) p)->dv0;
                ((PolyFT4_800458F4 *) prim)->u3 = t->u0 + ((ParamsB_800458F4 *) p)->du1;
                ((PolyFT4_800458F4 *) prim)->v3 = t->v0 + ((ParamsB_800458F4 *) p)->dv1;
            } else {
                ((PolyFT4_800458F4 *) prim)->u0 = t->u0;
                ((PolyFT4_800458F4 *) prim)->v0 = t->v0;
                ((PolyFT4_800458F4 *) prim)->u3 = t->u1;
                ((PolyFT4_800458F4 *) prim)->v3 = t->v1;
            }
            {
                u8 u3 = ((PolyFT4_800458F4 *) prim)->u3;
                u8 v0 = ((PolyFT4_800458F4 *) prim)->v0;
                u8 u0 = ((PolyFT4_800458F4 *) prim)->u0;
                u8 v3 = ((PolyFT4_800458F4 *) prim)->v3;

                ((PolyFT4_800458F4 *) prim)->u1 = u3;
                ((PolyFT4_800458F4 *) prim)->v1 = v0;
                ((PolyFT4_800458F4 *) prim)->u2 = u0;
                ((PolyFT4_800458F4 *) prim)->v2 = v3;
            }
            ((PTag_800458F4 *) prim)->addr = (*(PTag_800458F4 **) D_8008B3A0)[depth].addr;
            (*(PTag_800458F4 **) D_8008B3A0)[depth].addr = (u32) prim;
            prim += sizeof(PolyFT4_800458F4);
        } else {
            ((u8 *) &((PolyF4_800458F4 *) prim)->tag)[3] = 5;
            ((u8 *) &((PolyF4_800458F4 *) prim)->rgbc)[3] = 0x28;
            ((PolyF4_800458F4 *) prim)->rgbc = (arg0 & 0xFFFFFF) + 0x28000000;
            if (flags & 0x2000) {
                ((u8 *) &((PolyF4_800458F4 *) prim)->rgbc)[3] |= 2;
            }
            ((PolyF4_800458F4 *) prim)->x0 = x0;
            ((PolyF4_800458F4 *) prim)->y0 = y0;
            ((PolyF4_800458F4 *) prim)->x1 = x1;
            ((PolyF4_800458F4 *) prim)->y1 = y0;
            ((PolyF4_800458F4 *) prim)->x2 = x0;
            ((PolyF4_800458F4 *) prim)->y2 = y1;
            ((PolyF4_800458F4 *) prim)->x3 = x1;
            ((PolyF4_800458F4 *) prim)->y3 = y1;
            ((PTag_800458F4 *) prim)->addr = (*(PTag_800458F4 **) D_8008B3A0)[depth].addr;
            (*(PTag_800458F4 **) D_8008B3A0)[depth].addr = (u32) prim;
            prim += sizeof(PolyF4_800458F4);
        }
        *(u8 **) D_8008B3AC = prim;
    }
}
