#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern void SpuSetVoiceAttr(void *attr);

typedef struct S_800536F8 {
    u16 flags;
    u8 unk2;
    u8 pad3[0x3D];
    s32 unk40;
    u8 pad44[8];
    s32 unk4C;
} S_800536F8;

typedef struct VoiceAttr_8005336C {
    s32 mask;
    s32 unk4;
    u8 pad8[0xC];
    s16 unk14;
    u8 pad16[0x2A];
} VoiceAttr_8005336C;

extern S_800536F8 D_800B134C;

s32 func_8005336C(void) {
    VoiceAttr_8005336C attr;
    u32 mask;

    if (!D_8008A9EC) {
        printf(D_80010920, D_8008AA00, 0x2C2);
        exit(1);
    }

    attr.unk4 = 0x10;
    mask = 1 << D_800B134C.unk40;
    if (D_800B134C.flags & 0x200) {
        mask |= 1 << D_800B134C.unk4C;
    }
    attr.mask = mask;
    attr.unk14 = 0;
    SpuSetVoiceAttr(&attr);
    D_800B134C.unk2 = 5;
    return 0;
}
