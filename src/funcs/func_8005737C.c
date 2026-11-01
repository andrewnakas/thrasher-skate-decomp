#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
} PadInfo_5737C;

typedef struct {
    PadInfo_5737C *info;
    u8 pad4[8];
    u16 unkC;
    u16 unkE;
    u8 pad10[0x20];
} Pad_5737C;

typedef struct {
    s32 b[10];
} Map_5737C;

PadInfo_5737C *func_80034F14(s32);
extern Pad_5737C D_800B2C7C[2];
extern Map_5737C D_800B2CDC[3];
extern Map_5737C D_800B2D5C;

void func_8005737C(void) {
    PadInfo_5737C *info;
    u32 i;
    u32 j;

    for (i = 0; i < 2; i++) {
        info = func_80034F14(0);
        D_800B2C7C[i].info = info;
        D_800B2C7C[i].unkE = 0;
        D_800B2C7C[i].unkC = 0;
        if (info->flags & 1) {
            D_800B2C7C[i].unkE |= 1;
        }
    }
    for (j = 0; j < 3; j++) {
        switch (j) {
        default:
        case 0:
            D_800B2CDC[j].b[0] = 0x20;
            D_800B2CDC[j].b[1] = 0x80;
            D_800B2CDC[j].b[2] = 0x40;
            D_800B2CDC[j].b[3] = 0x10;
            D_800B2CDC[j].b[4] = 0x100;
            D_800B2CDC[j].b[5] = 0x200;
            D_800B2CDC[j].b[6] = 0xC00;
            D_800B2CDC[j].b[7] = 0x2000;
            D_800B2CDC[j].b[8] = 0x400;
            D_800B2CDC[j].b[9] = 0x800;
            break;
        case 1:
            D_800B2CDC[j].b[0] = 0x80;
            D_800B2CDC[j].b[1] = 0x40;
            D_800B2CDC[j].b[2] = 0x20;
            D_800B2CDC[j].b[3] = 0x10;
            D_800B2CDC[j].b[4] = 0x200;
            D_800B2CDC[j].b[5] = 0x800;
            D_800B2CDC[j].b[6] = 0x500;
            D_800B2CDC[j].b[7] = 0x2000;
            D_800B2CDC[j].b[8] = 0x400;
            D_800B2CDC[j].b[9] = 0x100;
            break;
        case 2:
            D_800B2CDC[j].b[0] = 0x80;
            D_800B2CDC[j].b[1] = 0x20;
            D_800B2CDC[j].b[2] = 0x10;
            D_800B2CDC[j].b[3] = 0x40;
            D_800B2CDC[j].b[4] = 0x100;
            D_800B2CDC[j].b[5] = 0x400;
            D_800B2CDC[j].b[6] = 0xA00;
            D_800B2CDC[j].b[7] = 0x2000;
            D_800B2CDC[j].b[8] = 0x200;
            D_800B2CDC[j].b[9] = 0x800;
            break;
        }
    }
    D_800B2D5C.b[0] = 0x20;
    D_800B2D5C.b[1] = 0x80;
    D_800B2D5C.b[2] = 0x40;
    D_800B2D5C.b[3] = 0x10;
    D_800B2D5C.b[4] = 0x100;
    D_800B2D5C.b[5] = 0x200;
    D_800B2D5C.b[6] = 0x50;
    D_800B2D5C.b[7] = 0x150;
    D_800B2D5C.b[8] = 0;
    D_800B2D5C.b[9] = 0;
}
