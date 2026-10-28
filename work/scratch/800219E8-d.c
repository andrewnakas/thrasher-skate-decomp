#include "common.h"

typedef struct {
    u8 f00[0xC];
    u16 *f0C;
} Ctx;

extern u8 D_8008A2AC;
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern s32 D_8009C0A4[];
extern s32 D_8009C6D4[];
extern u8 D_800AB794[];

s32 func_80020C34(u8, u8, u8, s32 **, s32 *, s32 *);

s32 func_800219E8(u32 id, Ctx *ctx, u8 extra) {
    u8 *tab;
    u8 *base;
    u32 cnt;
    s32 spare;
    u8 *node;
    u16 *rec;
    s32 next;
    u32 i;
    u32 j;

    rec = (u16 *) (D_800AB794 + 16 * *(u16 *) ctx->f0C);

    func_80020C34((u8) (id >> 16), (u8) ((id & 0xFF00) >> 8), D_8008A2AC, (s32 **) &tab, (s32 *) &cnt, &spare);

    base = tab;

    if ((id & 0xFF) >= cnt || (s32) (id & 0xFF) < 0) {
        return 1;
    }

    while (id != (u32) -1) {
        node = (u8 *) ((u32) (0x30 * (id & 0xFF)) + (u32) base);
        *(u16 *) (node + 0xE) = (u16) (*(u16 *) ((u8 *) rec + 2) + extra);

        D_8009C0A4[D_8008A2A4++] = (s32) id;

        for (i = 0; i < D_8008A2A8; i++) {
            if (D_8009C6D4[i] == (s32) id) {
                D_8008A2A8--;
                for (j = i; j < D_8008A2A8; j++) {
                    D_8009C6D4[j] = D_8009C6D4[j + 1];
                }
            }
        }

        id = *(s32 *) ((u32) (0x30 * (id & 0xFF)) + (u32) base + 0x2C);
    }

    return 0;
}
