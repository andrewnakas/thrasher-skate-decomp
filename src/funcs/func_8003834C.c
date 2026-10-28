#include "common.h"

typedef struct {
    u8 pad0[0x18];
    u32 unk18;
    u8 pad1C[0x28 - 0x1C];
} Ent_8003834C;

extern s32 D_8008A618;
extern s32 D_8008A644;
extern s32 D_8008B190;
extern u8 D_8008A66C[];
extern Ent_8003834C D_800A81AC[];

s32 func_80037BB8(void);
s32 func_80037C4C(void *p);

s32 func_8003834C(void) {
    s32 total;
    s32 i;

    total = 0x1E000;
    if (D_8008A618 != 0 && func_80037BB8() == 0) {
        D_8008A644 = 0;
        if (func_80037C4C(D_8008A66C) == 0) {
            for (i = 0; i < D_8008B190; i++) {
                total -= (D_800A81AC[i].unk18 + 0x1FFF) & -0x2000;
            }
            return total;
        }
    }
    return -1;
}
