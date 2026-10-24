#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk80036BF4Desc;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Unk80036BF4Desc *unkC;
    u8 pad10[8];
    u16 unk18;
    u16 unk1A;
    u8 unk1C;
    u8 pad1D[3];
    u8 buf[0x100];
    s32 unk120;
    s32 unk124;
} Unk80036BF4;

void func_800366D0(s32, s32, s32);
void func_80036020(void);
void func_80036074(void);
s32 func_80035F5C(s32, s32, s32);
s32 func_800363F8(void *, s32, s32);
s32 func_8003663C(s32, s32, s32);
void func_80036758(s32);
s32 func_800367F4(s32);
s32 func_80034C20(s32);
s32 func_80019F10(s32, s32, s32, s32, s32 *);
void func_80034BD8(s32);
void func_80036E04(Unk80036BF4 *);

s32 func_80036BF4(Unk80036BF4 *o, s32 arg) {
    s32 id;
    s32 v;
    s32 r = 0;
    s32 h;
    s32 tmp;

    if (o->unk18 == 0) {
        v = o->unkC->unk0;
        id = o->unkC->unk4 & 0xFFFFFF;
    } else {
        v = o->unkC->unk0;
        id = o->unkC->unk8;
    }
    func_800366D0(o->unk0, v + 0x10, 0);
    if (o->unk18 == 0) {
        func_80036020();
        if (o->unk1C == 0) {
            if (func_80035F5C(o->unk0, arg, id) == 0) {
                r = 1;
            }
        } else if (o->unk120 == (s32) o->unkC) {
            h = func_800363F8(o->buf, 1, 0);
            func_8003663C(h, arg, o->unk124);
            func_80036758(h);
        } else {
            if (func_80035F5C(o->unk0, (s32) o->buf, id) == 0) {
                r = 1;
            }
            h = func_800363F8(o->buf, 1, 0);
            id = func_800367F4(h);
            func_8003663C(h, arg, id);
            func_80036758(h);
            o->unk124 = id;
            o->unk120 = (s32) o->unkC;
        }
        func_80036074();
    } else {
        h = func_80034C20(id);
        func_80036020();
        if (func_80035F5C(o->unk0, h, id) == 0) {
            r = 1;
        }
        func_80036074();
        if (o->unk1A == 0) {
            func_80019F10(1, h, id, arg, &tmp);
        } else if (o->unk1A == 1) {
            func_80019F10(2, h, id, arg, &tmp);
        }
        func_80034BD8(h);
    }
    func_80036E04(o);
    return r;
}
