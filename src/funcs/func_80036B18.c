#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Unk80036B18Desc;

typedef struct {
    s32 unk0;
    u8 pad4[8];
    Unk80036B18Desc *unkC;
    u8 pad10[0xC];
    u8 unk1C;
    u8 pad1D[3];
    u8 buf[0x100];
    s32 unk120;
    s32 unk124;
} Unk80036B18;

extern u8 D_8008A5F8[];
void func_80036020(void);
void func_80036074(void);
void func_800366D0(s32, s32, s32);
s32 func_80035F5C(s32, s32, s32);
s32 func_800363F8(void *, s32, s32);
s32 func_800367F4(s32);
void func_80036758(s32);
s32 printf(void *, void *);

s32 func_80036B18(Unk80036B18 *o) {
    s32 id = o->unkC->unk4 & 0xFFFFFF;
    s32 h;

    if (o->unk1C != 0) {
        func_80036020();
        func_800366D0(o->unk0, o->unkC->unk0 + 0x10, 0);
        func_80035F5C(o->unk0, (s32) o->buf, id);
        func_80036074();
        h = func_800363F8(o->buf, 1, 0);
        if (h == 0) {
            printf(D_8008A5F8, o->buf);
        }
        id = func_800367F4(h);
        func_80036758(h);
        o->unk124 = id;
        o->unk120 = (s32) o->unkC;
    }
    return id;
}
