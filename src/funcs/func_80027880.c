#include "common.h"

extern u16 D_8008B018;
extern u32 D_8008B020;
extern u32 D_8008B024;
extern s32 D_8008B088;
extern s32 D_8008B08C;
extern s32 D_8008B090;
extern s32 D_8008B094;
extern s32 D_8008B098;
extern s32 D_8008B09C;
extern u8 D_8009CE50[];

u32 func_80027A9C(u32, u32);
void func_80029DAC(u8 *, u32);
void func_80027B44(u32);

void func_80027880(u8 *list, s32 idx) {
    u8 *e;
    u32 r;
    s32 t;

    r = func_80027A9C(D_8008B018 + idx, 0);
    e = (u8 *) (idx * 156 + (s32) D_8009CE50);
    func_80029DAC(e, r);
    func_80027B44(r);
    if (*(u32 *) (e + 0x2C) == 0) {
        return;
    }
    if (*(u16 *) *(u32 *) (e + 0x2C) == 0 || *(u16 *) *(u32 *) (e + 0x2C) == 2) {
        if (D_8008B020 != 0) {
            *(u32 *) (D_8008B020 + 0x94) = (u32) e;
        } else {
            *(u32 *) (list + 4) = (u32) e;
        }
        D_8008B020 = (u32) e;
    }
    if (*(u16 *) *(u32 *) (e + 0x2C) != 0) {
        return;
    }
    if (D_8008B024 != 0) {
        *(u32 *) (D_8008B024 + 0x98) = (u32) e;
    } else {
        *(u32 *) (list + 8) = (u32) e;
    }
    {
        u32 q = *(u32 *) (e + 0x2C);
        s32 lim = D_8008B088;

        D_8008B024 = (u32) e;
        t = (*(s32 *) (q + 4) - (*(s32 *) (q + 0x10) >> 1)) << 16;
        if (lim < t) {
            t = lim;
        }
        D_8008B088 = t;
    }
    t = (*(s32 *) (*(u32 *) (e + 0x2C) + 8) - (*(s32 *) (*(u32 *) (e + 0x2C) + 0x14) >> 1)) << 16;
    if (D_8008B08C < t) {
        t = D_8008B08C;
    }
    D_8008B08C = t;
    t = (*(s32 *) (*(u32 *) (e + 0x2C) + 0xC) - (*(s32 *) (*(u32 *) (e + 0x2C) + 0x18) >> 1)) << 16;
    if (D_8008B090 < t) {
        t = D_8008B090;
    }
    D_8008B090 = t;
    t = (*(s32 *) (*(u32 *) (e + 0x2C) + 4) + (*(s32 *) (*(u32 *) (e + 0x2C) + 0x10) >> 1)) << 16;
    if (t < D_8008B094) {
        t = D_8008B094;
    }
    D_8008B094 = t;
    t = (*(s32 *) (*(u32 *) (e + 0x2C) + 8) + (*(s32 *) (*(u32 *) (e + 0x2C) + 0x14) >> 1)) << 16;
    if (t < D_8008B098) {
        t = D_8008B098;
    }
    D_8008B098 = t;
    t = (*(s32 *) (*(u32 *) (e + 0x2C) + 0xC) + (*(s32 *) (*(u32 *) (e + 0x2C) + 0x18) >> 1)) << 16;
    if (t < D_8008B09C) {
        t = D_8008B09C;
    }
    D_8008B09C = t;
}
