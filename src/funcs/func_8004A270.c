#include "common.h"

extern void func_800330A4(s32 *v);

typedef struct S_8004A270 {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
} S_8004A270;

void func_8004A270(S_8004A270 *s) {
    s32 v[3];

    v[0] = s->unk8 - s->unk14;
    v[1] = s->unkC - s->unk18;
    v[2] = s->unk10 - s->unk1C;
    func_800330A4(v);
    s->unk20 = v[0] >> 4;
    s->unk22 = v[1] >> 4;
    s->unk24 = v[2] >> 4;
}
