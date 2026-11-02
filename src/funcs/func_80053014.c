/* a4 r5: case 2/3 ends in return 0 (keeps the return label between v0=0 and the epilogue). */
#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern void SpuSetVoiceAttr(void *attr);
extern void SpuFlush(s32);
extern void SpuSetIRQAddr(s32);
extern void SpuSetIRQ(s32);
extern void SpuSetKey(s32, u32);
extern void func_80053E98(void *);
extern u32 func_80053774(u32, s32 *, s32);

typedef struct Sub_80053014 {
    u8 pad0[8];
    u16 rate;
} Sub_80053014;

typedef struct S_80053014 {
    u16 flags;
    u8 unk2;
    u8 pad3;
    u32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    Sub_80053014 *unk20;
    u8 pad24[0x1C];
    s32 unk40;
    s32 unk44;
    u8 pad48[4];
    s32 unk4C;
} S_80053014;

typedef struct VoiceAttr_80053014 {
    s32 mask;
    s32 unk4;
    u8 pad8[0xC];
    s16 unk14;
    u8 pad16[0x2A];
} VoiceAttr_80053014;

extern S_80053014 D_800B134C;

s32 func_80053014(void) {
    VoiceAttr_80053014 attr;
    s32 pos;
    u32 mask;
    u32 vmask;

    if (!D_8008A9EC) {
        printf(D_80010920, D_8008AA00, 0x265);
        exit(1);
    }

    switch (D_800B134C.unk2) {
    case 2:
    case 3:
        D_800B134C.unk2 = 3;
        return 0;
    case 5:
        attr.unk4 = 0x10;
        vmask = 1 << D_800B134C.unk40;
        if (D_800B134C.flags & 0x200) {
            vmask |= 1 << D_800B134C.unk4C;
        }
        attr.mask = vmask;
        attr.unk14 = ((u32) D_800B134C.unk20->rate << 12) / 44100;
        SpuSetVoiceAttr(&attr);
        SpuFlush(0);
        D_800B134C.unk2 = 4;
        break;
    default:
        SpuSetIRQ(0);
        mask = 1 << D_800B134C.unk40;
        if (D_800B134C.flags & 0x200) {
            mask |= 1 << D_800B134C.unk4C;
        }
        SpuSetKey(0, mask);
        if (!(D_800B134C.flags & 0x800)) {
            func_80053E98(D_800B134C.unk20);
            D_800B134C.unk10 = 0;
            D_800B134C.unk2 = 3;
            if (func_80053774(D_800B134C.unk4, &pos, 1) < D_800B134C.unk4) {
                D_800B134C.flags |= 0x1000;
                D_800B134C.unk1C = pos;
            } else {
                D_800B134C.unk1C = 0;
                D_800B134C.flags &= ~0x1000;
            }
        } else {
            D_800B134C.unkC = 0;
            D_800B134C.unk14 = 0;
            D_800B134C.unk18 = 0;
            SpuSetIRQAddr(D_800B134C.unk44 + 0x800);
            SpuSetIRQ(1);
            mask = 1 << D_800B134C.unk40;
            if (D_800B134C.flags & 0x200) {
                mask |= 1 << D_800B134C.unk4C;
            }
            SpuSetKey(1, mask);
            D_800B134C.unk2 = 4;
        }
        break;
    }
    return 0;
}
