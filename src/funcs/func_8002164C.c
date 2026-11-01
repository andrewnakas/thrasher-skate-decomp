#include "common.h"

/* Active record, 0x30 bytes: a POLY_G4 followed by state. */
typedef struct {
    u8 pad0[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u8 r3, g3, b3, p3;
    s16 x3, y3;
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[6];
} T_8002164C_rec;

extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

u32 func_80020D74(s32, s32);
s32 func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

u32 func_8002164C(u8 arg0, s32 x, s32 y, s32 w, s32 h, u8 r0, u8 g0, u8 b0, u8 r1, u8 g1,
                  u8 b1, u8 abr) {
    T_8002164C_rec *sp18;
    s32 sp1C;
    s32 sp20;
    T_8002164C_rec *rec;
    u32 id;
    u32 i;
    u32 k;

    id = func_80020D74(arg0, 0);
    if (id != 0xFFFFFFFFU) {
        func_80020C34((id >> 16) & 0xFF, (id & 0xFF00) >> 8, D_8008A2AC, (s32 *) &sp18, &sp1C, &sp20);
        rec = &sp18[id & 0xFF];
        rec->len = 8;
        rec->code = 0x38;
        if (abr) {
            rec->code = 0x3A;
        }
        rec->x0 = x;
        rec->y0 = y;
        rec->r0 = r0;
        rec->g0 = g0;
        rec->b0 = b0;
        rec->x1 = x + w;
        rec->y1 = y;
        rec->r1 = r0;
        rec->g1 = g0;
        rec->b1 = b0;
        rec->x2 = x;
        rec->y2 = y + h;
        rec->r2 = r1;
        rec->g2 = g1;
        rec->b2 = b1;
        rec->x3 = x + w;
        rec->y3 = y + h;
        rec->r3 = r1;
        rec->g3 = g1;
        rec->b3 = b1;
        sp18[id & 0xFF].f28 = 4;
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
