#include "common.h"

extern u8 D_80092C84[];
extern u8 D_80092CB4[];
extern u8 D_800937C4[];
extern u8 D_80095D44[];
extern u8 D_80096C44[];
extern u8 D_8008AED4;
extern u8 D_8008A2AC;

s32 func_80020608(void) {
    u8 *b1 = D_80092C84;
    u8 *b1b = D_80092CB4;
    u8 *b2 = D_800937C4;
    u8 *b3 = D_80095D44;
    u8 *b4 = D_80096C44;
    s32 k;
    s32 n;
    s32 o;

    D_8008AED4 = 0;
    D_8008A2AC = 0;
    for (k = 0; k < 2; k++) {
        for (n = 0, o = 0; n < 0x1D; n++, o += 0x30) {
            *(u32 *) (b1 + o) = (*(u32 *) (b1 + o) & 0xFF000000) | ((u32) (b1b + o) & 0xFFFFFF);
        }
        for (n = 0, o = 0; n < 0x1E; n++, o += 0x30) {
            *(u8 *) (b1 + o + 3) = 0;
            *(s32 *) (b1 + o + 0x2C) = -1;
            *(u8 *) (b1 + o + 0x28) = 0;
        }
        for (n = 0, o = 0; n < 0x63; n++, o += 0x30) {
            *(u32 *) (b2 + o) = (*(u32 *) (b2 + o) & 0xFF000000) | ((u32) (b2 + o + 0x30) & 0xFFFFFF);
        }
        for (n = 0, o = 0; n < 0x64; n++, o += 0x30) {
            *(u8 *) (b2 + o + 3) = 0;
            *(s32 *) (b2 + o + 0x2C) = -1;
            *(u8 *) (b2 + o + 0x28) = 0;
        }
        for (n = 0, o = 0; n < 0x27; n++, o += 0x30) {
            *(u32 *) (b3 + o) = (*(u32 *) (b3 + o) & 0xFF000000) | ((u32) (b3 + o + 0x30) & 0xFFFFFF);
        }
        for (n = 0, o = 0; n < 0x28; n++, o += 0x30) {
            *(u8 *) (b3 + o + 3) = 0;
            *(s32 *) (b3 + o + 0x2C) = -1;
            *(u8 *) (b3 + o + 0x28) = 0;
        }
        for (n = 0, o = 0; n < 0xE0; n++, o += 0x30) {
            *(u32 *) (b4 + o) = (*(u32 *) (b4 + o) & 0xFF000000) | ((u32) (b4 + o + 0x30) & 0xFFFFFF);
        }
        for (n = 0, o = 0; n < 0xE1; n++, o += 0x30) {
            *(u8 *) (b4 + o + 3) = 0;
            *(s32 *) (b4 + o + 0x2C) = -1;
            *(u8 *) (b4 + o + 0x28) = 0;
        }
        b1 += 0x5A0;
        b1b += 0x5A0;
        b2 += 0x12C0;
        b3 += 0x780;
        b4 += 0x2A30;
    }
    return 0;
}
