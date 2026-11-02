#include "common.h"

#define getTPage(tp, abr, x, y) \
    ((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3ff) >> 6) | (((y) & 0x200) << 2))

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
    s16 x, y, w, h;
} Rect;

extern s32 D_8008A75C;
extern s32 D_8008A760;
extern s32 D_8008A764;
extern s32 D_8008B248;
extern s32 D_8008B24C;
extern u8 D_80082430[];

void func_8005A0A8(void *);
void func_80059D88(s32);

void func_8003BB1C(void) {
    Sprt a;
    DrMode m1;
    Sprt b;
    DrMode m2;
    Rect r1;
    Rect r2;
    u16 *img;
    u8 lvl;
    s32 x;
    s32 y;
    u8 c;

    if (D_8008A760 == 0 && D_8008A764 == 0) {
        return;
    }
    lvl = *(u8 *) &D_8008A75C;
    if (lvl != 0) {
        img = *(u16 **) D_80082430;
        r1.x = img[0];
        r1.y = img[1];
        r1.w = 0x40;
        r1.h = 0x80;
        r2.x = img[0x2E];
        r2.y = img[0x2F];
        r2.w = 0x40;
        r2.h = 0x80;
        ((u8 *) &a)[3] = 4;
        a.code = 0x64;
        ((u8 *) &b)[3] = 4;
        b.code = 0x66;
        for (y = 0; y < D_8008B24C; y += 0x80) {
            x = 0;
            if (x < D_8008B248) {
            xl:
                ((u8 *) &m1)[3] = 1;
                m1.code = 0xE1000600 | getTPage(2, 0, r1.x + x, r1.y + y);
                func_8005A0A8(&m1);
                c = 0x80 - lvl;
                a.r0 = c;
                a.g0 = c;
                a.b0 = c;
                if (y != 0x80) {
                    a.x0 = x;
                    a.y0 = y;
                    a.w = 0x40;
                    a.h = 0x80;
                    a.u0 = 0;
                    a.v0 = y;
                } else {
                    a.x0 = x;
                    a.y0 = y;
                    a.w = 0x40;
                    a.h = 0x7F;
                    a.u0 = 0;
                    a.v0 = y;
                }
                func_8005A0A8(&a);
                func_80059D88(0);
                ((u8 *) &m2)[3] = 1;
                m2.code = 0xE1000600 | getTPage(2, 1, r2.x + x, r2.y + y);
                func_8005A0A8(&m2);
                c = lvl + 8;
                b.r0 = c;
                b.g0 = c;
                b.b0 = c;
                if (y != 0x80) {
                    b.x0 = x;
                    b.y0 = y;
                    b.w = 0x40;
                    b.h = 0x80;
                    b.u0 = 0;
                    b.v0 = y;
                } else {
                    b.x0 = x;
                    b.y0 = y;
                    b.w = 0x40;
                    b.h = 0x7F;
                    b.u0 = 0;
                    b.v0 = y;
                }
                func_8005A0A8(&b);
                func_80059D88(0);
                x += 0x40;
                if (x < D_8008B248) goto xl;
            }
        }
    }
    if (D_8008A760 != 0) {
        D_8008A760--;
        return;
    }
    D_8008A75C += D_8008A764;
    if (D_8008A75C <= 0) {
        D_8008A75C = 0;
        D_8008A764 = 0;
    }
}
