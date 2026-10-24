#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
} Unk_80047414;

s16 func_80047414(Unk_80047414 *p) { return p->unk8; }
