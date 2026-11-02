#include "common.h"

extern s32 D_8008A9EC;
extern s32 D_8008A99C[2];
extern s32 D_8008A938[2];
extern s32 D_8008A9F4;
extern s32 D_8008A9FC;
extern s32 D_8008B454;
extern u32 D_8008B480;
extern s32 D_8008B4A0;
extern s32 D_8008B460[2];
extern void SpuSetVoiceAttr(void *attr);
extern void SpuFlush(s32);
extern s32 SpuIsTransferCompleted(s32);
extern void SpuFree(s32);
extern void SpuSetIRQCallback(s32);
extern void VSync(s32);
extern void func_80053224(void);
extern void func_80053B34(s32);
extern void func_8004E30C(u8 a0);
extern void func_8005CBD8(s32);
extern void func_8005CBEC(s32, s32, s32);

typedef struct Voice_8005263C {
    u8 id;
    u8 pad1[3];
    s32 voice;
    s32 addr;
} Voice_8005263C;

typedef struct S_8005263C {
    u16 flags;
    u8 unk2;
    u8 pad3;
    s32 unk4;
    u8 pad8[0x34];
    Voice_8005263C voices[2];
} S_8005263C;

typedef struct Node_8005263C {
    s32 unk0;
    s32 unk4;
    struct Node_8005263C *next;
} Node_8005263C;

typedef struct VoiceAttr_8005263C {
    s32 mask;
    s32 attr;
    u8 pad8[0x24];
    s32 unk2C;
    u8 pad30[6];
    s16 unk36;
    u8 pad38[8];
} VoiceAttr_8005263C;

extern S_8005263C D_800B134C;
extern Node_8005263C D_800B136C;

s32 func_8005263C(void) {
    VoiceAttr_8005263C attr;
    Node_8005263C *p;
    Node_8005263C *next;
    s32 *q;
    s32 *e;
    u32 i;
    s32 n;
    u32 mask;
    s32 one;

    if (D_800B134C.unk2 == 4) {
        one = 1;
        mask = one << D_800B134C.voices[0].voice;
        if (D_800B134C.flags & 0x200) {
            mask |= one << D_800B134C.voices[1].voice;
        }
        attr.attr = 0x4400;
        attr.unk2C = 3;
        attr.mask = mask;
        attr.unk36 = 0xF;
        SpuSetVoiceAttr(&attr);
        SpuFlush(0);
    }
    func_80053224();
    for (p = &D_800B136C; p != NULL; p = next) {
        next = p->next;
        func_80053B34(p->unk0);
        for (i = 0; i < 2; i++) {
            if ((s32 *) p == &D_8008B460[i * 4 + 1]) {
                D_8008B460[i * 4] = 0;
                D_8008B480 = i;
                break;
            }
        }
    }
    D_8008A9FC = D_8008A938[-1] * 10;
    {
        while (D_8008A9F4 != 0) {
            if (--D_8008A9FC == 0) {
                break;
            }
            VSync(0);
        }
        if (D_8008A9F4 != 0) {
            D_8008A9F4 = 0;
            D_8008B454 = 0;
            func_8005CBD8(0);
            func_8005CBEC(7, 0, 0);
        }
    }
    n = 0x3B;
    while (SpuIsTransferCompleted(0) == 0) {
        VSync(0);
        if (--n == 0) {
            break;
        }
    }
    for (i = 0; i <= ((D_800B134C.flags >> 9) & 1); i++) {
        func_8004E30C(D_800B134C.voices[i].id);
    }
    SpuFree(D_800B134C.voices[0].addr);
    D_8008A99C[-1] += D_800B134C.unk4;
    SpuSetIRQCallback(D_8008B4A0);
    D_8008A9EC = 0;
    return 0;
}
