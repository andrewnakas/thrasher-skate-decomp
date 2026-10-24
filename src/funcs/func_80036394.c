#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x5C];
} Unk80036394;

extern Unk80036394 D_800A677C[];

void func_80036394(s32 i) {
    D_800A677C[i - 1].unk0 = 0;
}
