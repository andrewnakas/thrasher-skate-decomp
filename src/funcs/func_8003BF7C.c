#include "common.h"

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 pad24[2];
    s16 unk26;
    u8 pad28[2];
    s16 unk2A;
    u8 pad2C[2];
    s16 unk2E;
} T_800A95D4;

typedef struct {
    u8 pad0[0xE8];
    s16 unkE8;
    s16 unkEA;
    s16 unkEC;
    s16 unkEE;
    s16 unkF0;
    s16 unkF2;
    s16 unkF4;
    s16 unkF6;
    s16 unkF8;
    s32 unkFC;
    s32 unk100;
    s32 unk104;
    s32 unk108[5];
    s32 unk11C;
    s32 unk120;
    s32 unk124;
} S_8008234C;

extern s32 D_8008ACEC;
extern T_800A95D4 D_800A95D4;
extern S_8008234C D_8008234C;

void func_80033E14(u32, T_800A95D4 *);
void TransposeMatrix(s16 *, s32 *);
void ApplyMatrixLV(s32 *, s32 *, s32 *);
void SetRotMatrix(s16 *);
void SetTransMatrix(s16 *);

void func_8003BF7C(void) {
    S_8008234C *p;
    T_800A95D4 *t;

    t = &D_800A95D4;
    func_80033E14((u32) (&D_8008ACEC)[-19] + 0x28, t);
    p = &D_8008234C;
    p->unkE8 = t->unk00 >> 4;
    p->unkEA = t->unk0C >> 4;
    p->unkEC = t->unk18 >> 4;
    p->unkEE = t->unk04 >> 4;
    p->unkF0 = t->unk10 >> 4;
    p->unkF2 = t->unk1C >> 4;
    p->unkF4 = t->unk08 >> 4;
    p->unkF6 = t->unk14 >> 4;
    p->unkF8 = t->unk20 >> 4;
    p->unkFC = t->unk26;
    p->unk100 = t->unk2A;
    p->unk104 = t->unk2E;
    TransposeMatrix(&p->unkE8, p->unk108);
    p->unk11C = -p->unkFC;
    p->unk120 = -p->unk100;
    p->unk124 = -p->unk104;
    ApplyMatrixLV(p->unk108, &p->unk11C, &p->unk11C);
    SetRotMatrix(&p->unkE8);
    SetTransMatrix(&p->unkE8);
}
