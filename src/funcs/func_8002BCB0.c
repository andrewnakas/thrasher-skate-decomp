#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x8];
    u16 f24;
} Ent_8002BCB0;

extern void (*D_8008A318)(s32, u32);

void func_8002BCB0(Ent_8002BCB0 *t) {
    u16 n = t->f24;

    if (n != 0 && D_8008A318 != 0) {
        D_8008A318(t->f18, n);
    }
}
