#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u8 unkC;
} Ent_800476FC;

s32 func_800476FC(Ent_800476FC *e, s16 v) {
    if (v < 0x100) {
        e->unkC = v;
    } else {
        e->unkC = 0;
    }
    return v;
}
