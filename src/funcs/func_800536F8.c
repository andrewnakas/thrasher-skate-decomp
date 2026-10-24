#include "common.h"

extern void SpuIsTransferCompleted(s32 a0);
extern void SpuSetIRQ(s32 a0);
extern void SpuSetKey(s32 a0, u32 a1);

typedef struct S_800536F8 {
    u16 flags;
    u8 unk2;
    u8 pad3[0x3D];
    s32 unk40;
    u8 pad44[8];
    s32 unk4C;
} S_800536F8;

extern S_800536F8 D_800B134C;

void func_800536F8(s32 a0) {
    u32 mask;

    if (a0 != 1) {
        return;
    }

    SpuIsTransferCompleted(1);
    SpuSetIRQ(0);

    mask = 1 << D_800B134C.unk40;
    if (D_800B134C.flags & 0x200) {
        mask |= 1 << D_800B134C.unk4C;
    }
    SpuSetKey(0, mask);
    D_800B134C.unk2 = 1;
}
