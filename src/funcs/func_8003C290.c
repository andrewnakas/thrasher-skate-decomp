/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    s16 m[3][3];
    s32 t[3];
} Mat_8003C290;

typedef struct {
    u8 pad0[2];
    u16 id;
    u16 f4;
    u8 pad6[2];
    u16 f8;
    u8 padA[0x12];
} Cell_8003C290;

typedef struct {
    s32 w;
    s32 h;
    u8 pad8[0x24];
    s32 f2C;
    u16 f30;
    u16 f32;
    u8 pad34[0xC];
} Prm_8003C290;

extern s32 func_80032C54(s32, s32);
extern s16 func_80032DCC(s32, s32);
extern void func_800458F4(u16, s32, s32, s32, Prm_8003C290 *);
extern s16 D_8008B274[8];
extern s16 D_8008B278[8];
extern s32 D_8008B2F0;
extern s32 D_8008B2F4;
extern s32 D_8008B2F8;
extern Cell_8003C290 *D_8008B2FC;

void func_8003C290(Mat_8003C290 *m, s32 arg1) {
    s32 size[2];
    Prm_8003C290 prm;
    Cell_8003C290 *c;
    s32 step;
    s32 a;
    s32 r;
    s32 frac;
    s32 x0;
    s32 col0;
    s32 row;
    s32 x;
    s32 y;
    s32 col;
    u16 id;

    size[0] = (func_80032C54(0x271C, D_8008B274[0]) * 102) >> 16;
    size[1] = (size[0] * 0x12C00) / 0x1E000;
    step = 0x10000 / D_8008B2F0;
    a = func_80032DCC(m->m[2][0], m->m[2][2]) * 360;
    a += (0x370000 - D_8008B278[-2] * 360) >> 1;
    if (a < 0) {
        a += 0x1680000;
    }
    r = func_80032C54(a, (s16) step * 360);
    if (r < 0) {
        frac = -(-r & 0xFFFF);
    } else {
        frac = r & 0xFFFF;
    }
    col0 = r >> 16;
    prm.f2C = 0x5FF;
    row = D_8008B2F4 - 1;
    prm.w = size[0];
    y = arg1 - size[1] + D_8008B2F8;
    prm.h = size[1];
    x0 = -((frac * size[0]) >> 16);
    for (; -size[1] < y && row >= 0; y -= size[1], row--) {
        col = col0;
        for (x = x0; x < 0x200; x += size[0]) {
            c = &D_8008B2FC[row * D_8008B2F0 + col];
            id = c->id;
            if (id != 0) {
                prm.f30 = c->f4;
                prm.f32 = c->f8;
                func_800458F4(id, x, y, 0x5204, &prm);
            }
            col++;
            if (col == D_8008B2F0) {
                col = 0;
            }
        }
    }
}
