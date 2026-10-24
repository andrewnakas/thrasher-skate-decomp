#include "common.h"

typedef struct {
    s32 unk0;
    u32 unk4;
} S80014338;

void func_80014338(S80014338 *arg0) {
    arg0->unk4 &= ~2;
}
