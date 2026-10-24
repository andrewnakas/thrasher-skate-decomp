#include "common.h"

typedef struct {
    u8 pad0[0x164];
    s32 unk164;
} S80014464;

void func_80014464(S80014464 *arg0, s32 arg1) {
    arg0->unk164 = arg1;
}
