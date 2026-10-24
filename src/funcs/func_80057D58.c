#include "common.h"

typedef struct {
    u16 *ptr;
    u8 pad4[0x2C];
} Rec_80057D58;

typedef struct {
    u8 pad0[0x69];
    u8 unk69;
    u8 pad6A;
    u8 unk6B;
    u8 pad6C[4];
} Ent_80057D58;

extern Ent_80057D58 D_800B2428[];
extern Rec_80057D58 D_800B2C7C[];
extern s32 func_80055D58(void);
extern void func_8003571C(u16 *, u16, u16, u16, s32);

void func_80057D58(s32 idx, u32 a1, u32 a2) {
    Ent_80057D58 *e;
    Rec_80057D58 *rec;
    u16 *p;
    u8 *base;

    base = (u8 *) D_800B2428;
    e = (Ent_80057D58 *) (base + idx * 0x70);
    if (e->unk6B == 0) {
        return;
    }
    if (func_80055D58() != 0) {
        return;
    }
    rec = &D_800B2C7C[e->unk69];
    if (a1 != 0) {
        p = rec->ptr + a1 * 3;
        if (p[0x11] < (a2 << 8)) {
            func_8003571C(rec->ptr, a1, (a2 << 8) & 0xFFFF,
                          (a2 >> 4) < 4 ? 4 : (a2 >> 4), 1);
        }
    } else {
        func_8003571C(rec->ptr, 0, a2 ? 0xFFFF : 0, 4, 0);
    }
}
