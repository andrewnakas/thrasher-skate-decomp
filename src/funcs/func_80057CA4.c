#include "common.h"

extern u8 D_800B2428[];
extern u8 D_800B2C7C[];
extern s32 D_8008B4E0;
extern s32 D_8008B4E4;

s32 *func_80057CA4(s32 idx, s32 sub) {
    u8 *base = D_800B2428;
    u8 *p = base + idx * 112;
    u8 *tbl = D_800B2C7C + p[0x69] * 48;
    u8 *e = tbl + sub * 8;

    D_8008B4E0 = *(s32 *) (e + 0x10);
    D_8008B4E4 = *(s32 *) (e + 0x14);
    if (sub == 0) {
        if (*(u32 *) (tbl + 4) & 4) {
            D_8008B4E0 = 0xFFFF0000;
        } else if (*(u32 *) (tbl + 4) & 8) {
            D_8008B4E0 = 0x10000;
        }
        if (*(u32 *) (tbl + 4) & 1) {
            D_8008B4E4 = 0xFFFF0000;
        } else if (*(u32 *) (tbl + 4) & 2) {
            D_8008B4E4 = 0x10000;
        }
    }
    return &D_8008B4E0;
}
