#include "common.h"

typedef struct {
    u8 pad0[4];
    u16 unk4;
} Ent_8003F9F0;

void func_8003F9F0(Ent_8003F9F0 *p, u16 v) {
    p->unk4 = v;
}
