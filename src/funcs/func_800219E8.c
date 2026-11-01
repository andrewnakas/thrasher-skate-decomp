#include "common.h"

typedef struct {
    u8 f00[0xE];
    s16 f0E;
    u8 f10[0x1C];
    s32 f2C;
} Node_800219E8;

typedef struct {
    u16 unk0;
    u16 base;
    u8 pad4[0xC];
} Tile_800219E8;

typedef struct {
    u8 pad0[0xC];
    u16 *tile;
} Src_800219E8;

extern u8 D_8008A2AC;
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern s32 D_8009C0A4[];
extern s32 D_8009C6D4[];
extern Tile_800219E8 D_800AB794[];

s32 func_80020C34(u8, u8, u8, s32 **, s32 *, s32 *);

s32 func_800219E8(u32 arg0, Src_800219E8 *src, s32 arg2) {
    u8 *tab;
    u32 cnt;
    s32 extra;
    Tile_800219E8 *t;
    u32 i;
    u32 j;
    s32 add;
    u32 id;

    add = arg2;
    t = &D_800AB794[*src->tile];
    id = arg0;
    func_80020C34((u8) (id >> 16), (u8) ((id & 0xFF00) >> 8), D_8008A2AC, (s32 **) &tab, (s32 *) &cnt, &extra);

    if ((id & 0xFF) >= cnt || (s32) (id & 0xFF) < 0) {
        return 1;
    }

    while (id != (u32) -1) {
        ((Node_800219E8 *) (tab + 0x30 * (id & 0xFF)))->f0E = t->base + (u8) add;
        D_8009C0A4[D_8008A2A4++] = id;

        for (i = 0; i < D_8008A2A8; i++) {
            if (D_8009C6D4[i] == (s32) id) {
                D_8008A2A8--;
                for (j = i; j < D_8008A2A8; j++) {
                    D_8009C6D4[j] = D_8009C6D4[j + 1];
                }
            }
        }

        id = ((Node_800219E8 *) (tab + 0x30 * (id & 0xFF)))->f2C;
    }

    return 0;
}
