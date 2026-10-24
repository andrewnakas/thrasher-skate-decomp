#include "common.h"

typedef struct {
    void *unk0;
    s32 unk4;
    u32 *unk8;
} S8001B0C0;

typedef struct {
    u8 pad0[0x3C];
    u32 unk3C;
} T8001B0C0;

void func_8001B0C0(S8001B0C0 *arg0) {
    if ((*arg0->unk8 & 0x200000) != 0) {
        T8001B0C0 *p = arg0->unk0;

        p->unk3C |= 0x40;
    }
}
