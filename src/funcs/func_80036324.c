#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8[4];
    s32 unkC;
    u8 unk10[8];
    s32 unk18;
    s32 unk1C;
    u8 unk20[0x40];
} Unk80036324;

extern Unk80036324 D_800A677C[];

s32 func_80036324(void) {
    Unk80036324 *r;
    s32 i;

    for (r = D_800A677C, i = 0; i < 0x14; r++, i++) {
        if (r->unk0 == 0) {
            r->unk8[0] = 0xFF;
            r->unk8[1] = 0xFF;
            r->unk8[2] = 0xFF;
            r->unk8[3] = 0xFF;
            r->unkC = -1;
            r->unk4 = 0;
            r->unk18 = 1;
            r->unk1C = 0;
            r->unk0 = -1;
            return i + 1;
        }
    }
    return 0;
}
