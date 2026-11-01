#include "common.h"

typedef struct Obj_8001F630 {
    u16 flags;
    u8 pad2[0x2D];
    u8 frame;
    u8 pad30[0xC];
    u16 unk3C;
    u16 count;
    s32 unk40;
    s8 *unk44;
    u8 *unk48;
    u32 *unk4C;
    u16 *unk50;
    s32 *unk54;
} Obj_8001F630;

typedef struct Ent_8001F630 {
    u16 unk0;
    u16 unk2;
    u8 pad4[0xC];
} Ent_8001F630;

extern Ent_8001F630 D_800AB794[];

extern s32 func_8001DD58(Obj_8001F630 *);
extern void func_8001DB74(Obj_8001F630 *);
extern void func_8002A564(s32, u16, u16);
extern void func_8002AAA8(s32, s8);
extern void func_8002AC14(u8 *, u32);
extern u16 func_800465B4(void);
extern void func_800465CC(s32 src, s32 dst);
extern void func_80046610(u16 src, u16 dst);

void func_8001F630(Obj_8001F630 *o) {
    Ent_8001F630 *e;
    s32 *p;
    s32 x;
    s32 t;
    s32 i;
    s32 n;
    u16 v;
    s32 a;
    s32 b;

    if (func_8001DD58(o) != 0) {
        if (o->flags & 1) {
            func_8001DB74(o);
        }
        return;
    }
    switch (o->flags & 0x3000) {
    case 0x1000:
        e = &D_800AB794[o->unk3C];
        t = (e->unk2 << 4) & 0x300;
        e->unk2 = (e->unk2 & 0xFFC0) | (((t + (o->frame << 4)) >> 4) & 0x3F);
        break;
    case 0x2000:
        if (!(o->flags & 0x20)) {
            return;
        }
        switch (o->flags & 0xC000) {
        case 0:
            func_800465CC(o->unk50[o->frame], o->unk3C);
            break;
        case 0x4000:
            func_80046610(o->unk50[o->frame], o->unk3C);
            break;
        case 0x8000:
            n = o->count;
            i = 0;
            v = func_800465B4();
            func_800465CC(o->unk50[0], v);
            p = o->unk54;
            for (; i < n; i++) {
                a = o->unk50[i];
                b = v;
                if (i < n - 1) {
                    b = o->unk50[i + 1];
                }
                while ((x = *p++) != 0) {
                    func_8002A564(x, b, a);
                }
                func_800465CC(b, a);
            }
            break;
        }
        break;
    }
    if (o->flags & 0x20) {
        if (o->unk40 != 0) {
            func_8002AAA8(o->unk40, o->unk44[o->frame]);
        }
        if (o->unk48 != 0 && o->unk4C != 0) {
            func_8002AC14(o->unk48, o->unk4C[o->frame]);
        }
    }
}
