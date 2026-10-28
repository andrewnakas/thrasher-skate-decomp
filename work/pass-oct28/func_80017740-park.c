#include "common.h"

typedef struct S_80017740_Rec {
    u16 unk0;
    u16 flags;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
} S_80017740_Rec;

extern s32 D_8008AD64;

extern S_80017740_Rec *func_80019630(s32 id);
extern S_80017740_Rec *func_80019670(s32 id);
extern S_80017740_Rec *func_80019444(void);
extern s32 func_80036A78(s32 a0, s32 a1, s32 a2);
extern s32 func_80036B18(s32 a0);
extern s32 func_800159D8(s32 a0);
extern s32 func_80015E8C(s32 a0);
extern void func_80036BF4(s32 a0, s32 a1);
extern void func_80015F10(s32 a0);
extern u8 *func_80019518(void);
extern void func_8001954C(S_80017740_Rec *p);
extern void func_80039D1C(void *p);

S_80017740_Rec *func_80017740(s32 a0, s32 a1) {
    S_80017740_Rec *e;
    S_80017740_Rec *p;
    u8 *base;
    s32 id;
    s32 flag;
    s32 bit2;
    s32 unk8;
    s32 unkC;
    s32 off;

    flag = a1;

    if ((a0 & 0xE000) != 0) {
        return 0;
    }

    id = a0 & 0xFFFF;
    p = func_80019630(id);
    if (p != 0) {
        return p;
    }

    e = func_80019670(id);
    if (e != 0) {
        bit2 = 1;
        if (e->flags & 1) {
            flag = 1;
        }
        unk8 = e->unk8;
        unkC = e->unkC;
    } else {
        bit2 = 0;
        unkC = 0;
        if (func_80036A78(D_8008AD64, id, bit2) != 0) {
            return 0;
        }
        unk8 = func_800159D8(func_80036B18(D_8008AD64));
        if (unk8 == 0) {
            return 0;
        }
        func_80036BF4(D_8008AD64, func_80015E8C(unk8));
        func_80015F10(unk8);
    }

    p = func_80019444();
    if (p == 0) {
        return 0;
    }

    p->flags = 0;
    if (flag != 0) {
        p->flags = 1;
    }
    if (bit2 != 0) {
        p->flags |= 2;
    }
    p->unk0 = a0;
    p->unk8 = unk8;
    p->unkC = unkC;

    base = func_80019518();
    off = *(s32 *) (base + 0xC);
    if (off != 0) {
        func_80039D1C(base + off);
    }
    func_8001954C(p);
    return p;
}
