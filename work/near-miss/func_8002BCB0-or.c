#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x8];
    u16 f24;
} Ent;

extern void (*D_8008A318)(s32);

void func_8002BCB0(Ent *t) {
    if (t->f24 == 0 || D_8008A318 == 0) {
        return;
    }
    D_8008A318(t->f18);
}
