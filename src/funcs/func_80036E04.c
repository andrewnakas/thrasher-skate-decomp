#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xE];
    u16 unk1E;
} Unk80036E04;

void func_80036E04(Unk80036E04 *p) {
    p->unkC = p->unkC + p->unk1E;
}
