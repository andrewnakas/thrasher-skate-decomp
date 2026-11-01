#include "common.h"

/* Active record, 0x30 bytes: a POLY_F4 followed by state. */
typedef struct {
    u8 pad0[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
    u8 pad18[0x10];
    u8 f28;
    u8 f29;
    u8 pad2A[6];
} T_80021450_rec;

extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

u32 func_80020D74(s32, s32);
s32 func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

u32 func_80021450(u8 arg0, s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b, u8 abr) {
    T_80021450_rec *sp18;
    s32 sp1C;
    s32 sp20;
    T_80021450_rec *rec;
    u32 id;
    u32 i;
    u32 k;

    id = func_80020D74(arg0, 0);
    if (id != 0xFFFFFFFFU) {
        func_80020C34((id >> 16) & 0xFF, (id & 0xFF00) >> 8, D_8008A2AC, (s32 *) &sp18, &sp1C, &sp20);
        rec = &sp18[id & 0xFF];
        rec->len = 5;
        rec->code = 0x28;
        rec->r0 = r;
        rec->g0 = g;
        rec->b0 = b;
        if (abr) {
            rec->code |= 2;
        }
        rec->x0 = x;
        rec->y0 = y;
        rec->x1 = x + w;
        rec->y1 = y;
        rec->x2 = x;
        rec->y2 = y + h;
        rec->x3 = x + w;
        rec->y3 = y + h;
        sp18[id & 0xFF].f28 = 3;
        sp18[id & 0xFF].f29 = abr;
        for (i = 0; i < D_8008A2A8; i++) {
            if (D_8009C6D4[i] == id) {
                D_8008A2A8 -= 1;
                for (k = i; k < D_8008A2A8; k++) {
                    D_8009C6D4[k] = D_8009C6D4[k + 1];
                }
            }
        }
        D_8009C0A4[D_8008A2A4++] = id;
        return id;
    }
    return -1;
}
