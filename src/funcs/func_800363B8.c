#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x50];
} Unk800363B8;

extern Unk800363B8 D_800A671C[];
void func_8005D02C(s32, Unk800363B8 *);

void func_800363B8(s32 i, s32 a, s32 v) {
    Unk800363B8 *p = &D_800A671C[i];

    p->unkC = v;
    func_8005D02C(a, p);
}
