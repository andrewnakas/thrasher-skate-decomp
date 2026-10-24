#include "common.h"

typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 pad20[0x40];
} Unk800366D0;

extern Unk800366D0 D_800A671C[];

void func_800366D0(s32 i, s32 v) {
    Unk800366D0 *p = &D_800A671C[i];
    p->unk1C = v;
}
