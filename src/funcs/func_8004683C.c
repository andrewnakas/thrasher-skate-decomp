#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 pad4[4];
} Ent_8004683C;

extern Ent_8004683C D_800828B4[];

u32 func_8004683C(u16 i, u16 a, u32 b) {
    Ent_8004683C *base = D_800828B4;
    Ent_8004683C *e = &base[i];
    u16 lo = e->unk0 + (a >> 1);
    u32 hi = e->unk2 + b;

    return lo | (hi << 16);
}
