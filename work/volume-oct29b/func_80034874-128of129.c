#include "common.h"

extern u8 D_800A5634[];
extern u8 D_800A5C80[];
extern u8 D_80082FE5[];
extern u16 D_8008B0DC;
extern u32 D_8008B0EC;

void func_8005A234(void *);
void func_8005A0A8(void *);
void func_80059D88(s32);
s32 func_80058FA4(void);
u8 *func_80034824(u32);

void func_80034874(void) {
    u8 buf[0x30];
    s32 lim;
    u8 *p;
    u8 *e;
    s32 x;
    s32 y;
    s32 n;
    s32 k;
    s32 r;
    u32 c;

    func_8005A234(buf + 0x20);
    buf[0x1B] = 1;
    c = (D_8008B0DC & 0x9FF) | 0xE1000400;
    *(u32 *) (buf + 0x1C) = c;
    lim = *(s16 *) (buf + 0x26) - 0x10;
    r = *(s16 *) (buf + 0x24) - 8;
    func_8005A0A8(buf + 0x18);
    buf[0x3] = 4;
    buf[0x7] = 0x64;
    buf[0x4] = 0x80;
    buf[0x5] = 0x80;
    buf[0x6] = 0x80;
    *(u16 *) (buf + 0xE) = D_8008B0DC;
    y = 0x10;
    p = D_800A5634;
    for (n = 0; n < 0x1A; n++) {
        x = 8;
        for (k = 0; k < 0x3E; k++) {
            if (p > D_800A5C80) {
                break;
            }
            c = *p++;
            if (c == 0x20 || c == 0) {
                x += 8;
                continue;
            }
            if ((D_80082FE5[c & 0xFF] & 2) != 0) {
                c = func_80058FA4() & 0xFF;
            }
            e = func_80034824(D_8008B0EC);
            if (r < (x & 0xFFFF) + e[1]) {
                x = 8;
                y += 8;
            }
            *(u16 *) (buf + 0x8) = x;
            *(u16 *) (buf + 0xA) = y;
            *(u16 *) (buf + 0x10) = e[1];
            *(u16 *) (buf + 0x12) = e[2];
            buf[0xC] = ((u8 *) &D_8008B0DC)[4] + e[4];
            buf[0xD] = ((u8 *) &D_8008B0DC)[5] + e[5];
            func_8005A0A8(buf);
            func_80059D88(0);
            x += e[1];
        }
        y += 8;
        if (lim < (y & 0xFFFF)) {
            break;
        }
    }
}
