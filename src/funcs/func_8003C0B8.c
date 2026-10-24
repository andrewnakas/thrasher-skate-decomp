#include "common.h"

typedef struct {
    u8 pad0[3];
    u8 unk3;
    u8 pad4[3];
    u8 unk7;
    u16 unk8;
    u16 unkA;
    u8 padC[4];
    u16 unk10;
    u16 unk12;
    u8 pad14[4];
    u16 unk18;
    u16 unk1A;
    u8 pad1C[4];
    u16 unk20;
    u16 unk22;
} TexPage_8003C0B8;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} DrawStp_8003C0B8;

extern TexPage_8003C0B8 D_800A9604[];
extern u8 D_8008B2B4[4];
extern u8 D_8008B2D4[4];
extern s32 D_8008B2A4;
extern s32 D_8008B2EC;
extern s32 D_8008B2FC;
extern void SetDrawStp(DrawStp_8003C0B8 *, s32);

void func_8003C0B8(void) {
    u16 i;
    TexPage_8003C0B8 *t;

    D_8008B2A4 = 0;
    for (i = 0; i < 2; i++) {
        t = &D_800A9604[i];
        t->unk3 = 8;
        t->unk7 = 0x38;
        t->unk8 = 0;
        t->unkA = 0;
        t->unk10 = 0x200;
        t->unk12 = 0;
        t->unk18 = 0;
        t->unk1A = 0;
        t->unk20 = 0x200;
        t->unk22 = 0;
        SetDrawStp((DrawStp_8003C0B8 *) (D_8008B2B4 + i * 12), 1);
        SetDrawStp((DrawStp_8003C0B8 *) (D_8008B2D4 + i * 12), 0);
    }
    D_8008B2EC = 0;
    D_8008B2FC = 0;
}
