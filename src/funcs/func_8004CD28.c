#include "common.h"

typedef struct Pool_8004CD28 {
    u8 type;
    u8 count;
    u16 base;
    u8 bits[8];
} Pool_8004CD28;

typedef struct Ctx_8004CD28 {
    u8 pad0[4];
    u16 last;
} Ctx_8004CD28;

extern char D_800107F8[];
extern char D_8008A950[];
extern u32 D_800AF8A4[];
extern u32 func_80011B48(void);

s32 func_8004CD28(Ctx_8004CD28 *ctx, Pool_8004CD28 *grp, u32 idx, Pool_8004CD28 *pool, s32 *out, s32 *out2) {
    u32 r;
    u32 i;
    u32 j;
    u32 v;
    s32 ret;

    switch (pool->type) {
    case 0:
        r = func_80011B48() % pool->count;
        for (i = 0; i < pool->count; i++) {
            if (!((pool->bits[r >> 3] >> (r & 7)) & 1)) {
                break;
            }
            if (++r == pool->count) {
                r = 0;
            }
        }
        if (i == pool->count) {
            if (grp->type & 0x20) {
                grp->bits[idx >> 3] |= 1 << (idx & 7);
                return 0;
            }
            for (j = 0; j < 8; j++) {
                pool->bits[j] = 0;
            }
        }
        ret = 1;
        if (!(grp->type & 0x20)) {
            *out = pool->base + r;
            if (*out == ctx->last) {
                if (pool->count < 2) {
                    return 0;
                }
                r++;
                r %= pool->count;
            }
        }
        *out = pool->base + r;
        pool->bits[r >> 3] |= 1 << (r & 7);
        return ret;
    case 1:
        if (pool->count >= 0x10) {
            printf(D_800107F8, D_8008A950, 0x2D8);
            exit(1);
        }
        r = D_800AF8A4[pool->count];
        *out = pool->base + r;
        if ((grp->type & 0x20) && r < 0x40 && ((pool->bits[r >> 3] >> (r & 7)) & 1)) {
            return 0;
        }
        return *out != ctx->last;
    case 2:
        if (pool->count >= 0x10) {
            printf(D_800107F8, D_8008A950, 0x2EE);
            exit(1);
        }
        v = D_800AF8A4[pool->count];
        if (v <= 100) {
            *out = pool->base + v;
            return 1;
        }
        if (v < 200) {
            *out = pool->base + 0x66;
            ret = 2;
            *out2 = pool->base + (D_800AF8A4[pool->count] - 100);
            return ret;
        }
        if (v == 200) {
            *out = pool->base + 0x65;
            return 1;
        }
        if (v < 300) {
            *out = pool->base + 0x67;
            ret = 2;
            *out2 = pool->base + (D_800AF8A4[pool->count] - 200);
            return ret;
        }
        printf(D_800107F8, D_8008A950, 0x305);
        exit(1);
    }
    return 0;
}
