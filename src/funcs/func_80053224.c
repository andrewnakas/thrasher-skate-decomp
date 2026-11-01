#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern void SpuSetVoiceAttr(void *attr);
extern void SpuSetIRQ(s32);
extern void SpuSetKey(s32, u32);

typedef struct {
    u8 pad0[8];
    u16 rate;
} Hdr_80053224;

typedef struct {
    u16 flags;
    u8 state;
    u8 pad3[0x1D];
    Hdr_80053224 *hdr;
    u8 pad24[8];
    s32 unk2C;
    u8 pad30[0x10];
    s32 voice;
    u8 pad44[8];
    s32 voice2;
} Strm_80053224;

typedef struct {
    u32 mask;
    u32 attr;
    u8 pad8[0xC];
    u16 pitch;
    u8 pad16[0x2A];
} VoiceAttr_80053224;

extern Strm_80053224 D_800B134C;

s32 func_80053224(void) {
    VoiceAttr_80053224 attr;
    u32 mask;

    if (!D_8008A9EC) {
        printf(D_80010920, D_8008AA00, 0x2A1);
        exit(1);
    }
    D_800B134C.unk2C = 0;
    switch (D_800B134C.state) {
    case 3:
        D_800B134C.state = 2;
        break;
    case 5: {
        u32 m;

        attr.attr = 0x10;
        m = 1 << D_800B134C.voice;
        if (D_800B134C.flags & 0x200) {
            m |= 1 << D_800B134C.voice2;
        }
        attr.mask = m;
        attr.pitch = (u32)(D_800B134C.hdr->rate << 12) / 44100;
        SpuSetVoiceAttr(&attr);
    }
    case 4:
        SpuSetIRQ(0);
        mask = 1 << D_800B134C.voice;
        if (D_800B134C.flags & 0x200) {
            mask |= 1 << D_800B134C.voice2;
        }
        SpuSetKey(0, mask);
        D_800B134C.state = 1;
        break;
    }
    return 0;
}
