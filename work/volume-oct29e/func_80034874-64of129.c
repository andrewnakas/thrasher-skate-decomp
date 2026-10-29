#include "common.h"

typedef struct {
    u8 pad0[3];
    u8 f3;
    u8 f4;
    u8 f5;
    u8 f6;
    u8 f7;
    s16 x;
    s16 y;
    u8 f12;
    u8 f13;
    s16 f14;
    s16 f16;
    s16 f18;
    u8 pad1[4];
} REC1;

typedef struct {
    u8 pad0[3];
    u8 f3;
    u32 f4;
} REC2;

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad1[0x58];
} REC3;

extern u8 D_800A5634[];
extern u8 D_800A5C80[];
extern u8 D_80082FE5[];
extern u8 D_8008B0DC[8];
extern u32 D_8008B0EC;

void func_8005A234(void *);
void func_8005A0A8(void *);
void func_80059D88(s32);
s32 func_80058FA4(void);
u8 *func_80034824(u32);

void func_80034874(void) {
    REC1 a;
    REC2 b;
    REC3 c;
    s32 lim;
    u8 *hdr;
    u8 *p;
    u8 *e;
    s32 x;
    s32 y;
    s32 n;
    s32 k;
    s32 r;
    u32 v;

    p = D_800A5634;
    func_8005A234(&c);
    hdr = D_8008B0DC;
    y = 0x10;
    n = 0;
    b.f3 = 1;
    v = (*(u16 *) hdr & 0x9FF) | 0xE1000400;
    b.f4 = v;
    lim = c.f6 - 0x10;
    r = c.f4 - 8;
    func_8005A0A8(&b);
    a.f3 = 4;
    a.f7 = 0x64;
    a.f4 = 0x80;
    a.f5 = 0x80;
    a.f6 = 0x80;
    a.f14 = *(u16 *) (hdr + 2);
    do {
        x = 8;
        for (k = 0; k < 0x3E; k++) {
            if (p > D_800A5C80) {
                break;
            }
            v = *p++;
            if (v == 0x20 || v == 0) {
                x += 8;
                continue;
            }
            if ((D_80082FE5[v & 0xFF] & 2) != 0) {
                v = func_80058FA4() & 0xFF;
            }
            e = func_80034824(D_8008B0EC);
            if (r < (x & 0xFFFF) + e[1]) {
                x = 8;
                y += 8;
            }
            a.x = x;
            a.y = y;
            a.f16 = e[1];
            a.f18 = e[2];
            a.f12 = hdr[4] + e[4];
            a.f13 = hdr[5] + e[5];
            func_8005A0A8(&a);
            func_80059D88(0);
            x += e[1];
        }
        y += 8;
        if (lim < (y & 0xFFFF)) {
            break;
        }
        n++;
    } while (n < 0x1A);
}
