#include "common.h"

typedef struct {
    s32 unk0;
    u32 unk4;
} S80014450;

void func_80014450(S80014450 *arg0) {
    arg0->unk4 |= 0x20;
}
