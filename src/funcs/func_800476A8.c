#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u8 unkC;
} Ent_800476A8;

s16 func_800476A8(Ent_800476A8 *e) {
    if (e->unkC != 0) {
        return e->unkC;
    }
    return 0x100;
}
