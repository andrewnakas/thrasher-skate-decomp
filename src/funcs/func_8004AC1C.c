#include "common.h"

typedef struct S_8004AC1C_Sub {
    u8 pad0[0xC];
    s32 unkC;
    struct S_8004AC1C_Sub *unk10;
} S_8004AC1C_Sub;

typedef struct S_8004AC1C_Item {
    u16 flags;
    u8 pad2[0x2A];
    u32 unk2C;
    u32 unk30;
    u8 pad34[4];
    S_8004AC1C_Sub *unk38;
} S_8004AC1C_Item;

typedef struct S_8004AC1C_Rec {
    u8 pad0[0xC];
    void (*fn)(struct S_8004AC1C_Rec *);
} S_8004AC1C_Rec;

extern s32 D_8008A938;
extern u8 D_800AEA24[0x80];

extern void func_8004BD20(S_8004AC1C_Sub *p);
extern s32 func_8004B41C(S_8004AC1C_Item *e);
extern void func_8004B4A8(S_8004AC1C_Item *e, S_8004AC1C_Rec *rec);
extern s32 func_8004B448(S_8004AC1C_Item *e);
extern void func_8004AF80(s32 a0);

s32 func_8004AC1C(void) {
    S_8004AC1C_Item *e;
    S_8004AC1C_Sub *p;
    S_8004AC1C_Rec rec;
    u32 i;
    u32 s0;
    s32 v;

    if (D_8008A938 != 0) {
        return 0;
    }

    for (i = 0; (i & 0xFF) < 0x20; i++) {
        e = *(S_8004AC1C_Item **) (D_800AEA24 + (i & 0xFF) * 4);
        if (e == 0) {
            continue;
        }

        if (e->unk38 != 0) {
            e->unk38->unkC--;
        }

        p = e->unk38;
        while (p != 0 && p->unkC == 0) {
            func_8004BD20(p);
            p = p->unk10;
        }
        e->unk38 = p;

        if (func_8004B41C(e) == 0) {
            continue;
        }

        s0 = e->unk30;
        if (s0 < e->unk2C) {
            e->unk2C -= s0;
        } else {
            for (;;) {
                s0 -= e->unk2C;
                func_8004B4A8(e, &rec);
                if (rec.fn != 0) {
                    rec.fn(&rec);
                }
                if (func_8004B41C(e) == 0) {
                    if (e->flags & 4) {
                        func_8004AF80(i & 0xFF);
                    }
                    break;
                }
                v = func_8004B448(e) << 12;
                e->unk2C = v;
                if (s0 >= v) {
                    continue;
                }
                break;
            }
            e->unk2C -= s0;
        }
    }
    return 0;
}
