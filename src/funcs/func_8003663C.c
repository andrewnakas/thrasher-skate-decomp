#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    u8 pad1C[0x44];
} Unk8003663C;

extern Unk8003663C D_800A677C[];
void func_80036020(void);
void func_80036074(void);
s32 func_80035F5C(s32, s32, s32);

s32 func_8003663C(s32 a0, s32 a1, s32 a2) {
    if (D_800A677C[a0 - 1].unk18 != 1) {
        return 0;
    }
    func_80036020();
    if (func_80035F5C(a0, a1, a2) == 0) {
        return 0;
    }
    func_80036074();
    return 1;
}
