#include "common.h"

typedef struct {
    u8 pad0[0x28];
    s32 unk28;
    u8 pad2C[0xAC];
    s32 unkD8;
    u8 padDC[0x38];
    u8 unk114;
    u8 unk115;
    u8 pad116[2];
    s32 unk118[3];
    s16 unk124[3];
    u8 pad12A[6];
    s32 unk130;
    u16 unk134[0x3B];
    u8 unk1AA;
    u8 pad1AB;
} Ent_80014EE8;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[0x30];
    Ent_80014EE8 *ents;
} Obj_80014EE8;

extern s32 D_8008AD2C;
extern s32 D_8008AD30;
typedef struct {
    u8 pad0[0xC];
    u16 unkC;
    u8 padE[0x12];
    u16 unk20;
} G_80014EE8;
extern G_80014EE8 D_80092524;

extern s32 func_800123B0(Obj_80014EE8 *, s32, u16, u8 *, s32);
extern s32 func_800132FC(s32 *);
extern void func_80013A98(u16 *, u16 *, u16 *, u8);
extern void func_80013BA8(u16 *, u16 *, u16 *, u8);
extern void func_80013CE8(s32 *, s32 *, s32 *);
extern void func_80013D34(s32 *, s32 *, s32 *);
extern void func_80014C60(u16 *, u16 *, u16 *, s32, s32);
extern s32 func_80032C28(s32, s32);
extern void func_80034D4C(u16 *, u16 *, s32);

s32 *func_80014EE8(Obj_80014EE8 *obj, s32 a1, s32 a2, u16 *pad, s32 t) {
    Ent_80014EE8 *p[4];
    Ent_80014EE8 *e;
    u8 i;
    s32 n;
    s32 one;

    one = 0x10000;
    e = obj->ents;
    obj->flags |= 0x4000;
    for (i = 0; i < 4; i++) {
        p[i] = &obj->ents[i + 1];
    }
    p[2]->unkD8 = a1;
    p[3]->unkD8 = a2;
    D_8008AD30 = func_800123B0(obj, one, pad[1], (u8 *) &D_80092524 + 0x14, 3);
    D_8008AD2C = func_800123B0(obj, one, pad[0], (u8 *) &D_80092524, 2);
    func_80014C60(p[2]->unk134, p[3]->unk134, p[0]->unk134, t, e->unk115);
    p[0]->unk130 = func_80032C28(p[2]->unk130, t) + func_80032C28(p[3]->unk130, 0x10000 - t);
    for (i = 0; i < 3; i++) {
        p[0]->unk118[i] = func_80032C28(p[2]->unk118[i], t) + func_80032C28(p[3]->unk118[i], 0x10000 - t);
        p[0]->unk124[i] = (func_80032C28(p[2]->unk124[i] << 16, t) + func_80032C28(p[3]->unk124[i] << 16, 0x10000 - t)) >> 16;
    }
    if (pad[0] & 2) {
        if (pad[0] & 0x80) {
            p[1]->unkD8 = 0;
            ((u8 *) obj->ents)[0x85D] = 0;
        } else if (p[1]->unkD8 != 0) {
            n = p[0]->unk115 * 3;
            for (i = 0; i < n; i++) {
                p[1]->unk134[i] = e->unk134[i];
            }
            p[1]->unk118[0] = e->unk118[0];
            p[1]->unk118[1] = e->unk118[1];
            p[1]->unk118[2] = e->unk118[2];
            p[1]->unk130 = e->unk130;
            D_80092524.unk20 = D_80092524.unkC;
            ((u8 *) obj->ents)[0x85D] = 3;
        } else {
            ((u8 *) obj->ents)[0x85D] = 0;
        }
        e->unk115 = p[0]->unk115;
        e->unk114 = p[0]->unk114;
    }
    switch (((u8 *) obj->ents)[0x85D]) {
    case 0:
        func_80034D4C(e->unk134, p[0]->unk134, e->unk115 * 6);
        e->unk118[0] = p[0]->unk118[0];
        e->unk118[1] = p[0]->unk118[1];
        e->unk118[2] = p[0]->unk118[2];
        e->unk130 = p[0]->unk130;
        break;
    case 4:
        func_80034D4C(e->unk134, p[1]->unk134, e->unk115 * 6);
        if (func_800132FC(p[1]->unk118) == 0) {
            e->unk118[0] = p[1]->unk118[0];
            e->unk118[1] = p[1]->unk118[1];
            e->unk118[2] = p[1]->unk118[2];
        } else {
            e->unk118[0] = p[0]->unk118[0];
            e->unk118[1] = p[0]->unk118[1];
            e->unk118[2] = p[0]->unk118[2];
        }
        e->unk130 = p[1]->unk130;
        break;
    case 2:
        e->unk130 = (p[0]->unk130 + p[1]->unk130) >> 1;
        func_80013A98(p[0]->unk134, p[1]->unk134, e->unk134, e->unk115);
        if (func_800132FC(p[1]->unk118) == 0) {
            func_80013CE8(p[0]->unk118, p[1]->unk118, e->unk118);
        } else {
            e->unk118[0] = p[0]->unk118[0];
            e->unk118[1] = p[0]->unk118[1];
            e->unk118[2] = p[0]->unk118[2];
        }
        break;
    case 3:
        e->unk130 = (p[0]->unk130 + p[1]->unk130 + p[1]->unk130 + p[1]->unk130) >> 2;
        func_80013BA8(p[0]->unk134, p[1]->unk134, e->unk134, e->unk115);
        if (func_800132FC(p[1]->unk118) == 0) {
            func_80013D34(p[0]->unk118, p[1]->unk118, e->unk118);
        } else {
            e->unk118[0] = p[0]->unk118[0];
            e->unk118[1] = p[0]->unk118[1];
            e->unk118[2] = p[0]->unk118[2];
        }
        break;
    case 1:
        e->unk130 = (p[1]->unk130 + p[0]->unk130 + p[0]->unk130 + p[0]->unk130) >> 2;
        func_80013BA8(p[1]->unk134, p[0]->unk134, e->unk134, e->unk115);
        if (func_800132FC(p[1]->unk118) == 0) {
            func_80013D34(p[1]->unk118, p[0]->unk118, e->unk118);
        } else {
            e->unk118[0] = p[0]->unk118[0];
            e->unk118[1] = p[0]->unk118[1];
            e->unk118[2] = p[0]->unk118[2];
        }
        break;
    }
    if (((u8 *) obj->ents)[0x85D] != 0) {
        ((u8 *) obj->ents)[0x85D]--;
    }
    e->unk1AA = p[0]->unk1AA;
    e->unk28 = p[0]->unk28;
    if (!(pad[0] & 0x80)) {
        p[1]->unkD8 = a1;
    }
    e->unkD8 = a1;
    e->unk118[0] = p[0]->unk118[0];
    e->unk118[1] = p[0]->unk118[1];
    e->unk118[2] = p[0]->unk118[2];
    e->unk124[0] = p[0]->unk124[0];
    e->unk124[1] = p[0]->unk124[1];
    e->unk124[2] = p[0]->unk124[2];
    return &D_8008AD2C;
}
