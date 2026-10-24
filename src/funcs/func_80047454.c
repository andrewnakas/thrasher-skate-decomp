#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
} Unk_80047454;

s16 func_80047454(Unk_80047454 *p) { return p->unkA; }
