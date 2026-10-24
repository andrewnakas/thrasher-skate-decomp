#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} S80016264;

s32 func_800162D0(S80016264 *);

void func_80016264(S80016264 *arg0) {
    arg0->unkC = func_800162D0(arg0);
}
