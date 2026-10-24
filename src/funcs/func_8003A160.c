#include "common.h"

typedef struct {
    u16 v[4];
} Ent_8003A160;

extern Ent_8003A160 D_800A8404[];
extern void func_8004862C(u16 packed, s16 v);

void func_8003A160(u8 i) {
    Ent_8003A160 *base;
    Ent_8003A160 *e;

    base = D_800A8404;
    e = &base[i];
    func_8004862C((e->v[1] << 6) | ((e->v[0] >> 4) & 0x3F), e->v[2]);
    e->v[2] = 0;
}
