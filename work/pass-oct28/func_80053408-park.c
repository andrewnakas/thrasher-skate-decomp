#include "common.h"

typedef struct S_80053408_Attr {
    u32 mask;
    s32 unk4;
    u16 volL;
    u16 volR;
    u8 padC[0x34];
} S_80053408_Attr;

typedef struct S_80053408_Spu {
    u16 flags;
    u8 unk2;
    u8 pad3[0x3D];
    s32 unk40;
    u8 pad44[8];
    s32 unk4C;
} S_80053408_Spu;

extern S_80053408_Spu D_800B134C;
extern s32 D_8008A9EC;
extern u8 D_800B1378[0x40];
extern s32 D_800B138C;
extern char D_80010920[];
extern char D_8008AA00[];

extern s32 printf(char *fmt, char *arg, s32 line);
extern void exit(s32 code);
extern void SpuSetVoiceAttr(S_80053408_Attr *attr);

s32 func_80053408(s32 a0, s32 a1) {
    S_80053408_Attr attr;
    s32 l;
    s32 r;
    s32 v;

    if (D_8008A9EC == 0) {
        printf(D_80010920, D_8008AA00, 0x2D9);
        exit(1);
    }

    *(s32 *) D_800B1378 = 0;
    attr.unk4 = 3;

    if ((s8) a1 > 0) {
        l = (a0 & 0xFF) * (0x7F - (s8) a1) >> 7;
        r = a0 & 0xFF;
    } else if ((s8) a1 < 0) {
        r = (a0 & 0xFF) * ((s8) a1 + 0x7F) >> 7;
        l = a0 & 0xFF;
    } else {
        l = a0 & 0xFF;
        r = l;
    }

    if (D_800B134C.flags & 0x200) {
        attr.mask = 1 << D_800B134C.unk40;
        attr.volR = 0;
        if ((a0 & 0xFF) != 0) {
            attr.volL = (l << 7) | 0x7F;
        } else {
            attr.volL = 0;
        }
        SpuSetVoiceAttr(&attr);

        attr.mask = 1 << D_800B134C.unk4C;
        attr.volL = 0;
        if ((a0 & 0xFF) != 0) {
            attr.volR = (r << 7) | 0x7F;
        }
    } else {
        if ((a0 & 0xFF) != 0) {
            attr.volL = (l << 7) | 0x7F;
            attr.volR = (r << 7) | 0x7F;
        } else {
            attr.volR = 0;
            attr.volL = 0;
        }
        attr.mask = 1 << D_800B138C;
    }

    SpuSetVoiceAttr(&attr);
    return 0;
}
