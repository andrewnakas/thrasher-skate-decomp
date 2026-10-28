#include "common.h"

typedef unsigned long long u64;

typedef struct {
    u16 flags;   /* 0x00 */
    u8 state;    /* 0x02 */
    u8 pad3[0x1D];
    u8 *unk20;   /* 0x20 */
    s32 unk24;   /* 0x24 */
    s32 unk28;   /* 0x28 */
    s32 unk2C;   /* 0x2C */
    u8 pad30[0x10];
    u32 unk40;   /* 0x40 */
    u8 pad44[8];
    u32 unk4C;   /* 0x4C */
} Spu_80053224;

extern Spu_80053224 D_800B134C;
extern u32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];
extern s32 printf(const char *, ...);
extern void exit(s32);
extern void SpuSetIRQ(s32);
extern void SpuSetKey(s32, u32);
extern void SpuSetVoiceAttr(void *);

s32 func_80053224(void) {
    Spu_80053224 *s;
    u32 attr[16];
    u32 mask;
    u32 v;
    u32 hi;

    if (D_8008A9EC == 0) {
        printf(D_80010920, D_8008AA00, 0x2A1);
        exit(1);
    }
    s = &D_800B134C;
    s->unk2C = 0;
    switch (s->state) {
    case 3:
        s->state = 2;
        return 0;
    case 5:
        attr[0] = 0;
        attr[1] = 0x10;
        mask = 1 << s->unk40;
        if (s->flags & 0x200) {
            mask |= 1 << s->unk4C;
        }
        attr[0] = mask;
        v = *(u16 *) (s->unk20 + 8);
        hi = (u32) ((((u64) (v << 12)) * 0xBE37C63Bu) >> 47);
        *(u16 *) ((u8 *) attr + 0x14) = hi;
        SpuSetVoiceAttr(attr);
        break;
    case 4:
        break;
    default:
        return 0;
    }
    SpuSetIRQ(0);
    s = &D_800B134C;
    mask = 1 << s->unk40;
    if (s->flags & 0x200) {
        mask |= 1 << s->unk4C;
    }
    SpuSetKey(0, mask);
    s->state = 1;
    return 0;
}
