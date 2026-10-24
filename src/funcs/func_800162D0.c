#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3;
    s32 unk4;
    s32 unk8;
} S800162D0;

s32 func_800162D0(S800162D0 *arg0) {
    return (s32)arg0 + arg0->unk0 + arg0->unk1 + arg0->unk2 + arg0->unk4 + arg0->unk8;
}
