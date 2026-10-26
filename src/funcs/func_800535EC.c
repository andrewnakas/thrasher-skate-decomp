#include "common.h"

extern void SpuIsTransferCompleted(s32);
extern void SpuSetIRQAddr(s32);
extern void SpuSetIRQ(s32);
extern void SpuSetKey(s32, u32);

typedef struct S_800535EC {
    u16 flags;
    u8 unk2;
    u8 pad3[9];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x24];
    s32 unk40;
    s32 unk44;
    u8 pad48[4];
    s32 unk4C;
} S_800535EC;

extern S_800535EC D_800B134C;

void func_800535EC(s32 stop) {
    S_800535EC *s;
    u32 mask;

    if (stop == 0) {
        s = &D_800B134C;
        D_800B134C.flags |= 0x800;
        if (s->unk2 == 3) {
            s->unkC = 0;
            s->unk14 = 0;
            s->unk18 = 0;
            SpuSetIRQAddr(s->unk44 + 0x800);
            SpuSetIRQ(1);
            mask = 1 << s->unk40;
            if (D_800B134C.flags & 0x200) {
                mask |= 1 << s->unk4C;
            }
            SpuSetKey(1, mask);
            s->unk2 = 4;
        } else if (s->unk2 == 2) {
            s->unk2 = 1;
        }
    } else {
        SpuIsTransferCompleted(1);
        SpuSetIRQ(0);
        mask = 1 << D_800B134C.unk40;
        if (D_800B134C.flags & 0x200) {
            mask |= 1 << D_800B134C.unk4C;
        }
        SpuSetKey(0, mask);
        D_800B134C.unk2 = 1;
    }
}
