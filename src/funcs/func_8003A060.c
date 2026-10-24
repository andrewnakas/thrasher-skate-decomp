#include "common.h"

typedef struct {
    u16 v[4];
} Ent_8003A060;

extern Ent_8003A060 D_800A8404[256];

void func_8003A060(void) {
    s32 i;
    Ent_8003A060 *e;

    for (i = 0; i < 256; i++) {
        e = &D_800A8404[i];
        e->v[0] = 0;
        e->v[1] = 0;
        e->v[2] = 0;
        e->v[3] = 0;
    }
}
