#include "common.h"

typedef struct {
    u8 type;
    u8 pad1[3];
    u32 key;
    u8 b[4];
} Ent35C9C;

extern Ent35C9C D_800A6294[];
extern s32 D_8008B108;

void func_80035C9C(u8 *p, s32 i) {
    Ent35C9C *base;
    Ent35C9C *e;
    u8 hi;
    u8 lo;

    base = D_800A6294;
    e = &base[i];
    hi = p[2];
    lo = p[3];

    e->type = 7;
    e->key = (u16) ~(lo | (hi << 8)) | 0x80000000;
    e->b[0] = p[6];
    e->b[1] = p[7];
    e->b[2] = p[4];
    e->b[3] = p[5];
    D_8008B108++;
}
