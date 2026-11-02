#include "common.h"

typedef struct {
    u32 voice;          /* 0x00 */
    u32 mask;           /* 0x04 */
    s16 vol_l;          /* 0x08 */
    s16 vol_r;          /* 0x0A */
    u8 padC[0x34];
} SpuAttr_80051844;

typedef struct {
    u16 flags;
    u8 pad02[0x36];
    s32 f38;
    u8 pad3C[0x10];
    s32 index4C;
    u8 pad50[8];
    s32 index58;
} Voice_80051844;

extern s32 D_8008A9C8;
extern char D_800108B0[];
extern char D_8008A9D4[];

extern s32 printf(const char *, ...);
extern void exit(s32);
extern void SpuSetVoiceAttr(SpuAttr_80051844 *);

s32 func_80051844(Voice_80051844 *v, u8 vol, s8 pan) {
    SpuAttr_80051844 attr;
    s32 l;
    s32 r;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x43E);
        exit(1);
    }
    v->f38 = 0;
    attr.mask = 3;
    if (pan > 0) {
        l = (vol * (0x7F - pan)) >> 7;
        r = vol;
    } else if (pan < 0) {
        l = vol;
        r = (vol * (pan + 0x7F)) >> 7;
    } else {
        r = vol;
        l = r;
    }
    if (!(v->flags & 0x100)) {
        if (vol != 0) {
            attr.vol_l = (l << 7) | 0x7F;
            attr.vol_r = (r << 7) | 0x7F;
        } else {
            attr.vol_r = 0;
            attr.vol_l = 0;
        }
        attr.voice = 1 << v->index4C;
        SpuSetVoiceAttr(&attr);
    } else {
        if (vol != 0) {
            attr.vol_l = (l << 7) | 0x7F;
            attr.vol_r = 0;
            attr.voice = 1 << v->index4C;
            SpuSetVoiceAttr(&attr);
            attr.vol_l = 0;
            attr.vol_r = (r << 7) | 0x7F;
            attr.voice = 1 << v->index58;
            SpuSetVoiceAttr(&attr);
        } else {
            attr.vol_r = 0;
            attr.vol_l = 0;
            attr.voice = 1 << v->index4C;
            SpuSetVoiceAttr(&attr);
            attr.voice = 1 << v->index58;
            SpuSetVoiceAttr(&attr);
        }
    }
    return 0;
}
