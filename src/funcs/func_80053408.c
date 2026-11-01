#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern void exit(s32) __attribute__((noreturn));
extern void SpuSetVoiceAttr(void *attr);
extern s32 D_800B1378[];
extern s32 D_800B138C[];

typedef struct S_80053408 {
    u16 flags;
    u8 unk2;
    u8 pad3[0x3D];
    s32 unk40;
    u8 pad44[8];
    s32 unk4C;
} S_80053408;

typedef struct VoiceAttr_80053408 {
    s32 mask;
    s32 attr;
    s16 left;
    s16 right;
    u8 pad[0x34];
} VoiceAttr_80053408;

extern S_80053408 D_800B134C;

s32 func_80053408(s32 vol, s8 pan) {
    VoiceAttr_80053408 a;
    s32 l;
    s32 r;

    if (!D_8008A9EC) {
        printf(D_80010920, D_8008AA00, 0x2D9);
        exit(1);
    }
    D_800B1378[0] = 0;
    a.attr = 3;
    if (pan > 0) {
        s32 v = (u8) vol;

        l = (v * (0x7F - pan)) >> 7;
        r = v;
    } else if (pan < 0) {
        s32 v = (u8) vol;

        r = (v * (pan + 0x7F)) >> 7;
        l = v;
    } else {
        r = (u8) vol;
        l = r;
    }
    if (!(D_800B134C.flags & 0x200)) {
        if ((u8) vol) {
            a.left = (l << 7) | 0x7F;
            a.right = (r << 7) | 0x7F;
        } else {
            a.right = 0;
            a.left = 0;
        }
        a.mask = 1 << D_800B138C[0];
        SpuSetVoiceAttr(&a);
    } else {
        if ((u8) vol) {
            a.left = (l << 7) | 0x7F;
            a.right = 0;
            a.mask = 1 << D_800B134C.unk40;
            SpuSetVoiceAttr(&a);
            a.left = 0;
            a.right = (r << 7) | 0x7F;
            a.mask = 1 << D_800B134C.unk4C;
            SpuSetVoiceAttr(&a);
        } else {
            a.right = 0;
            a.left = 0;
            a.mask = 1 << D_800B134C.unk40;
            SpuSetVoiceAttr(&a);
            a.mask = 1 << D_800B134C.unk4C;
            SpuSetVoiceAttr(&a);
        }
    }
    return 0;
}
