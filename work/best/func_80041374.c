#include "common.h"

typedef struct {
    u32 f00;
    u16 f04;
    u16 f06;
    u16 f08;
    u16 f0A;
    u16 f0C;
    u16 f0E;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1C;
    u32 f20;
    u32 f24;
} T_80041374;

extern u32 D_8008B344;
extern u32 D_8008B348;
extern u32 D_8008B34C;
extern u32 D_8008B350;
extern u32 D_8008B354;

void func_800403DC(T_80041374 *);
void func_80040594(T_80041374 *);
void func_8004095C(T_80041374 *);
s32 func_80041538(u32);
void func_800416A8(u32);
void func_80042230(T_80041374 *, s32, s32);
void func_80042338(T_80041374 *);

void func_80041374(T_80041374 *p, s32 a1, u32 a2) {
    u32 e;
    s32 i;

    D_8008B348 = a2;
    if (a2 & 1) {
        func_80042230(p, -0x381, 0);
    }
    D_8008B344 = a1;
    D_8008B34C = (u32) p;
    D_8008B354 = -1;
    D_8008B348 = a2;
    D_8008B350 = p->f24 + 0x10;
    if (D_8008B348 & 0x10) {
        if (p->f0E != 0) {
            i = 0;
            do {
                e = *(u32 *) (i * 16 + p->f24 + 0x10);
                if (e != 0) {
                    if ((*(u16 *) e & 1) == 0) {
                        func_800416A8(e);
                        *(u16 *) e |= 1;
                    }
                    if (*(u16 *) (e + 0x12) != 0) {
                        *(u16 *) e &= 0xFFFD;
                    }
                }
                i++;
            } while (i < p->f0E);
        }
    } else {
        e = p->f10;
        do {
            e = func_80041538(e);
        } while (e != 0);
    }
    if (D_8008B348 & 8) {
        func_800403DC(p);
        func_80040594(p);
    }
    if (D_8008B348 & 4) {
        func_8004095C(p);
    }
    if (D_8008B348 & 0x20) {
        e = p->f10;
        i = 0;
        if (p->f06 != 0) {
            do {
                *(u32 *) (e + 0x24) = 0;
                *(u32 *) (e + 0x20) = 0;
                i++;
                e += 0x34;
            } while (i < p->f06);
        }
    }
    if (p->f00 & 2) {
        func_80042338(p);
    }
}
