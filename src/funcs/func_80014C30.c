#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} S80014C30;

void func_80014C30(S80014C30 *arg0, S80014C30 *arg1) {
    arg0->unk1A = arg1->unk1A;
    arg0->unk1C = arg1->unk1C;
    arg0->unk1E = arg1->unk1E;
    arg0->unk18 = arg1->unk18;
}
