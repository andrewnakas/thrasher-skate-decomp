#include "common.h"

typedef struct {
    u16 v[4];
} Ent_80039D90;

typedef struct {
    union {
        u16 start;
        u8 id[2];
    } u;
    u16 count;
    u16 col[256];
} Pal_80039D90;

extern Ent_80039D90 D_800A8404[256];

u8 func_8003A09C(s16, s32, s32, s32 *);
void func_8003AE98(u16 *, u16 *, s32);
void func_80059D88(s32);

void func_80039D90(Pal_80039D90 *p) {
    u8 ids[8];
    s32 buf[2];
    u16 hdr[4];
    u16 clut[256];
    u16 i;
    s32 j;
    s32 mode;
    u16 c;

    mode = 0;

    if (p->count > 0x100) {
        p->count = 0x100;
    }
    for (i = mode; i < p->count; i++) {
        c = ((u16 *) p + i)[2];
        if (c == 0x7C1F) {
            ((u16 *) p + i)[2] = 0;
        } else {
            ((u16 *) p + i)[2] = c | 0x8000;
        }
    }
    for (i = 0; i < 2; i++) {
        ids[i] = func_8003A09C(p->count, 0, mode, buf);
        if (ids[i] == 0) {
            return;
        }
        {
        s32 k;
        for (k = 0xFF; k >= 0; k--) {
            clut[k] = 0;
        }
        }
        for (j = 0; j < p->count; j++) {
            c = p->col[j];
            clut[p->u.start + j] = c;
        }
        if (i == 0) {
            clut[0] = 0x8000;
        } else {
            clut[0] = 0;
        }
        hdr[0] = D_800A8404[ids[i]].v[0];
        hdr[1] = D_800A8404[ids[i]].v[1];
        hdr[2] = p->count;
        hdr[3] = D_800A8404[ids[i]].v[3];
        func_8003AE98(hdr, clut, 0);
        func_80059D88(0);
    }
    p->u.id[0] = ids[0];
    p->u.id[1] = ids[1];
}
