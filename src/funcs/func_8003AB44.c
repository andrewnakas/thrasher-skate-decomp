#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 unk2;
} Unk_8003AB44;

u16 func_8003AB44(Unk_8003AB44 *p) { return p->unk2; }
