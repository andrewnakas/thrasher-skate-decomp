#include "common.h"

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 w, h;
} Sprt;

typedef struct {
    u32 tag;
    u32 code;
} DrMode;

typedef struct {
    u8 pad0[4];
    s16 w;
    s16 h;
    u8 pad1[0x58];
} Env;

typedef struct {
    u16 tpage;
    u16 clut;
    u8 u;
    u8 v;
} TimInfo;

extern u8 D_800A5634[];
extern u8 D_800A5C80[];
extern u8 D_80082FE5[];
extern TimInfo D_8008B0DC;
extern s32 D_8008B0EC;

void func_8005A234(void *);
void func_8005A0A8(void *);
void func_80059D88(s32);
s32 func_80058FA4(s32);
u8 *func_80034824(s32, s32);

void func_80034874(void) {
    Sprt a;
    DrMode b;
    Env c;
    s32 lim;
    u8 *p;
    u8 *e;
    u16 x;
    u16 y;
    s32 n;
    s32 k;
    s32 r;
    s32 ch;
    TimInfo *t;

    p = D_800A5634;
    func_8005A234(&c);
    ((u8 *) &b)[3] = 1;
    b.code = (D_8008B0DC.tpage & 0x9FF) | 0xE1000400;
    r = c.w - 8;
    lim = c.h - 0x10;
    func_8005A0A8(&b);
    y = 0x10;
    n = 0;
    t = &D_8008B0DC;
    ((u8 *) &a)[3] = 4;
    a.code = 0x64;
    a.r0 = 0x80;
    a.g0 = 0x80;
    a.b0 = 0x80;
    a.clut = t->clut;
    do {
        x = 8;
        for (k = 0; k < 0x3E; k++) {
            if (p > D_800A5C80) {
                break;
            }
            ch = *p++;
            if (ch != 0x20 && ch != 0) {
            if (D_80082FE5[ch & 0xFF] & 2) {
                ch = func_80058FA4(ch & 0xFF) & 0xFF;
            }
            e = func_80034824(D_8008B0EC, ch);
            if (r < x + e[1]) {
                x = 8;
                y += 8;
            }
            a.x0 = x;
            a.y0 = y;
            a.w = e[1];
            a.h = e[2];
            a.u0 = t->u + e[4];
            a.v0 = t->v + e[5];
            func_8005A0A8(&a);
            func_80059D88(0);
            x += e[1];
            } else {
                x += 8;
            }
        }
        y += 8;
        n++;
        if (lim < y) {
            break;
        }
    } while (n < 0x1A);
}
