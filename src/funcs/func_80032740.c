#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect_80032740;

typedef struct {
    u32 mode;
    Rect_80032740 *crect;
    u32 *caddr;
    Rect_80032740 *prect;
    u32 *paddr;
} Tim_80032740;

typedef struct {
    u8 addr[3];
    u8 len;
    u32 code;
} TPage_80032740;

typedef struct {
    u8 addr[3];
    u8 len;
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
} Sprt_80032740;

typedef struct {
    u8 pad0[0x17];
    u8 f17;
    u8 pad18[0x6F];
    u8 f87;
    u8 pad88[0x5C];
    u16 *fE4;
} Gfx_80032740;

extern s32 func_80032644(u32 *, Tim_80032740 *, s32 *, s32 *, s32 *);
extern void func_8003AE98(Rect_80032740 *, u32 *, s32);
extern void func_8003B418(s32);
extern void func_8003B478(s32, s32);
extern void func_8003B8C8(s32, s32, s32);
extern void func_80059CF0(s32);
extern void func_80059D88(s32);
extern void func_8005A0A8(void *);
extern Gfx_80032740 D_8008234C;

s32 func_80032740(u32 *data) {
    Tim_80032740 tim;
    Rect_80032740 rect;
    TPage_80032740 tp;
    Sprt_80032740 sp;
    s32 scale;
    s32 mode;
    s32 col;
    s32 w;
    s32 step;
    u16 clut;
    s32 x;
    s32 y;
    s32 h;
    Sprt_80032740 *s;

    if (func_80032644(data, &tim, &scale, &mode, &col) != 0) {
        return 1;
    }
    if ((tim.mode & 7) == 1) {
        scale = 2;
        col = 0x7F;
        mode = 1;
    } else if ((tim.mode & 7) == 0) {
        scale = 4;
        col = 0xFF;
        mode = 0;
    } else {
        col = 0x3F;
        scale = 1;
        mode = 2;
    }
    w = tim.prect->w * scale;
    func_8003B478(w, tim.prect->h);
    func_8003B8C8(0, 0, 0);
    D_8008234C.f17 = 1;
    D_8008234C.f87 = 1;
    if (mode == 2) {
        rect.x = *D_8008234C.fE4;
        rect.y = *D_8008234C.fE4;
        rect.w = tim.prect->w;
        rect.h = tim.prect->h;
        func_8003AE98(&rect, tim.paddr, 1);
    } else {
        rect.x = 0x280;
        rect.y = 0;
        rect.w = tim.prect->w;
        rect.h = tim.prect->h;
        func_8003AE98(&rect, tim.paddr, 1);
        rect.x = 0x300;
        rect.y = 0x120;
        rect.w = tim.crect->w;
        rect.h = tim.crect->h;
        func_8003AE98(&rect, tim.caddr, 1);
        clut = (rect.y << 6) | ((rect.x >> 4) & 0x3F);
        step = scale << 6;
        for (y = 0; y < tim.prect->h; y += 0x100) {
            for (x = 0; x < w; x += step) {
                tp.len = 1;
                tp.code = ((mode & 3) << 7) | ((y & 0x100) >> 4)
                        | (((((x / step) << 6) + 0x280) & 0x3FF) >> 6) | ((y & 0x200) << 2) | 0xE1000600;
                func_8005A0A8(&tp);
                s = &sp;
                s->len = 4;
                s->code = 0x64;
                s->r0 = 0x80;
                s->g0 = 0x80;
                s->b0 = 0x80;
                s->x0 = x;
                s->y0 = y;
                s->u0 = 0;
                s->v0 = 0;
                s->clut = clut;
                s->w = step;
                h = tim.prect->h - y;
                if (h > 0x100) {
                    h = 0x100;
                }
                s->h = h;
                func_8005A0A8(s);
                func_80059D88(0);
            }
        }
    }
    func_8003B418(1);
    func_80059CF0(1);
    D_8008234C.f17 = 0;
    D_8008234C.f87 = 0;
    return 0;
}
