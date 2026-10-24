#include "common.h"

typedef struct {
    s32 unk0;
    u32 unk4;
} S80014310;

void func_80014310(S80014310 *arg0) {
    arg0->unk4 &= ~1;
}
