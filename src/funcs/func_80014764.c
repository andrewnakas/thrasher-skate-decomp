#include "common.h"

typedef struct {
    u8 pad0[0x38];
    u8 *unk38;
} S80014764;

typedef struct {
    u8 pad0[0x130];
    s32 unk130;
} T80014764;

void func_80014764(S80014764 *arg0, s32 arg1) {
    ((T80014764 *)arg0->unk38)->unk130 = arg1;
}
