#include "common.h"

extern s32 D_80089F54;
extern u16 D_80089F50;

typedef struct {
    u8 pad0[0x18];
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
} S80014784;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} T80014784;

void func_80014784(S80014784 *arg0, T80014784 *arg1) {
    if (D_80089F54 != 0) {
        arg1->unk2 = -arg1->unk2;
    }
    arg1->unk2 += D_80089F50;
    arg0->unk1A = arg1->unk0;
    arg0->unk1C = arg1->unk2;
    arg0->unk1E = arg1->unk4;
    arg0->unk18 = arg1->unk2;
}
