#include "common.h"

typedef struct {
    u8 pad0[0x1BC];
    s32 unk1BC;
} S800142B4;

void func_800142B4(S800142B4 *arg0, s32 arg1) {
    arg0->unk1BC = arg1;
}
