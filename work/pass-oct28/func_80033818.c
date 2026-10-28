#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 unk4;   /* 0x04 */
    s32 unk8;   /* 0x08 */
    s32 unkC;   /* 0x0C */
    u8 pad10[4];
    s32 unk14;  /* 0x14 */
    s32 unk18;  /* 0x18 */
    s32 unk1C;  /* 0x1C */
} Rec_80033818;

void func_80033818(Rec_80033818 *p) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;

    a = p->unk4;
    b = p->unkC;
    c = p->unk8;
    d = p->unk18;
    e = p->unk14;
    f = p->unk1C;
    p->unkC = a;
    p->unk4 = b;
    p->unk18 = c;
    p->unk8 = d;
    p->unk1C = e;
    p->unk14 = f;
}
