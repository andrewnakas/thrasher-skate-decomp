#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} S800161DC;

s32 func_80016248(S800161DC *);

void func_800161DC(S800161DC *arg0) {
    arg0->unkC = func_80016248(arg0);
}
