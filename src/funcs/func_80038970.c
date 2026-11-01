#include "common.h"

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
} Line_80038970;

extern Line_80038970 *func_80039FF4(u32 *, Line_80038970 *, u16);
extern u32 *D_8008B1A0;
extern u16 D_8008B1A4;
/* D_8008B3AC accessed as D_8008B3B0[-1] for the game's unsplit lui/lw */
extern Line_80038970 *D_8008B3B0[2];

void func_80038970(u32 rgb, u8 semi, s32 abr, s32 x0, s32 y0, s32 x1, s32 y1) {
    Line_80038970 *p;
    u32 *ot;
    u16 tp;
    s32 cur;

    p = D_8008B3B0[-1];
    ((u8 *) p)[3] = 3;
    p->code = 0x40;
    p->r0 = rgb;
    p->g0 = rgb >> 8;
    p->x0 = x0;
    p->y0 = y0;
    p->x1 = x1;
    p->y1 = y1;
    p->b0 = rgb >> 16;
    if (semi == 1) {
        p->code |= 2;
    }
    tp = abr & 3;
    p->y0 += 0x78;
    p->y1 += 0x78;
    ot = D_8008B1A0;
    p->tag = (p->tag & 0xFF000000) | (*ot & 0xFFFFFF);
    cur = D_8008B1A4;
    *ot = (*ot & 0xFF000000) | ((u32) p & 0xFFFFFF);
    p++;
    if (cur != ((tp << 5) | 0x80)) {
        p = func_80039FF4(ot, p, (tp << 5) | 0x80);
    }
    D_8008B3B0[-1] = p;
    D_8008B1A0--;
}
