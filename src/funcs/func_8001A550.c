#include "common.h"

extern s32 D_8008ADCC;
typedef struct {
    s32 key;
    u8 pad4[0x14];
} Ent_8001A550;

extern Ent_8001A550 D_80092654[];
extern s32 func_8001AFC8(void *, s32, u32);
extern s32 func_8001B0C0(void *);
extern s32 func_8001B0FC(s32, s32, s32);
extern s32 func_8001A834(void *, void *, s32, s32);
extern s32 func_8001C3CC(s32);
extern s32 func_8001B3F4(s32);
extern s32 func_8001C2F0(s32, s32, s32, s32, s32, s32, s32);
extern s32 func_800142B4(s32, s32);
extern s32 func_80014294(s32, s32, s32);
extern s32 func_80032C28(s32, s32);
extern s32 func_800122CC(s32, void *);

typedef struct Owner_8001A550 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Owner_8001A550;

typedef struct Obj_8001A550 {
    u8 pad0[0x54];
    u16 unk54;
    u8 pad56[0x178 - 0x56];
    u16 unk178;
} Obj_8001A550;

typedef struct Sub_8001A550 {
    u8 pad0[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} Sub_8001A550;

s32 func_8001A550(Owner_8001A550 *a0) {
    Obj_8001A550 *o;
    u8 *entry;
    u8 *base;
    s32 i;
    u16 h;
    u16 f;
    s32 key;
    s32 r;
    s32 v;
    s32 out[3];

    entry = 0;
    for (i = 0; i < D_8008ADCC; i++) {
        if (a0->unk0 == D_80092654[i].key) {
            entry = (u8 *) &D_80092654[i];
            break;
        }
    }

    o = (Obj_8001A550 *) a0->unk0;
    h = o->unk178;
    if (a0->unk10 != 0) {
        func_8001AFC8((void *) a0->unk8, a0->unk4, h);
    }
    func_8001B0C0(a0);
    func_8001B0FC(a0->unk0, a0->unk4, ((Sub_8001A550 *) a0->unk8)->unkC);

    f = h & 0xFFFF;
    if (f == 0) {
        func_8001A834((void *) a0->unk8, entry + 4, *(u16 *) (entry + 0x14), 0);
        v = func_8001C3CC(0x11);
        r = func_8001B3F4(v);
        ((Obj_8001A550 *) a0->unk0)->unk54 = r;
        func_8001C2F0(0x11, 0, r & 0xFFFF, 0, 0, v, 1);
    }

    func_800142B4(a0->unk0, ((Sub_8001A550 *) a0->unk8)->unk10);
    func_80014294(a0->unk0, f, *(u16 *) (entry + 0x14));
    out[0] = func_80032C28(((Sub_8001A550 *) a0->unk8)->unk14, (*(u8 *) (*(s32 *) (entry + 0x10) + 3)) << 9);
    out[1] = func_80032C28(((Sub_8001A550 *) a0->unk8)->unk18, (*(u8 *) (*(s32 *) (entry + 0x10) + 3)) << 9);
    out[2] = func_80032C28(((Sub_8001A550 *) a0->unk8)->unk1C, (*(u8 *) (*(s32 *) (entry + 0x10) + 3)) << 9);
    func_800122CC(a0->unk0, out);
    return 0;
}
