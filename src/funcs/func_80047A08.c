#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u32 unk14;
} Ent_80047A08;

extern void func_80034BD8(u32 p);

void func_80047A08(Ent_80047A08 *e) {
    if (e->unk14 != 0) {
        func_80034BD8(e->unk14);
    }
    e->unk14 = 0;
}
