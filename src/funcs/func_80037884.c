#include "common.h"

typedef struct Obj80037884 Obj80037884;

struct Obj80037884 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 unk18[0xC];
    void (*unk24)(Obj80037884 *, s32, s32);
    s32 unk28;
};

extern s32 D_8008A590;
extern u8 D_800A6EFC[];
s32 func_8005D130(void *);
void func_8005D02C(s32, void *);
void func_80034D4C(s32, u8 *, s32);

s32 func_80037884(Obj80037884 *o) {
    s32 n;

    if (D_8008A590 != func_8005D130(o->unk18)) {
        return 0;
    }
    n = o->unk8;
    if ((u32) (0x800 - o->unkC) < (u32) n) {
        n = 0x800 - o->unkC;
    }
    func_80034D4C(o->unk14, D_800A6EFC + o->unkC, n);
    o->unk8 -= n;
    if (o->unk8 != 0) {
        o->unk14 += n;
        o->unkC = 0;
        func_8005D02C(func_8005D130(o->unk18) + 1, o->unk18);
        return 0;
    }
    o->unk0 = 0;
    o->unk4 = 0;
    if (o->unk24 != 0) {
        o->unk24(o, o->unk28, o->unk0);
    }
    return 1;
}
