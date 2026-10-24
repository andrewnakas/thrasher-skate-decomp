#include "common.h"

typedef struct {
    u8 pad0[0x38];
    u8 *unk38;
} S80014770;

s32 func_80014770(S80014770 *arg0) {
    return *(s32 *)(arg0->unk38 + 0x130);
}
