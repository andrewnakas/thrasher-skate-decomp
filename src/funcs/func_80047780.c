#include "common.h"

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
} Ent_80047780;

s32 func_80047780(Ent_80047780 *e, s16 v) {
    if (v < 0x100) {
        e->unkD = v;
    } else {
        e->unkD = 0;
    }
    return v;
}
