#include "common.h"

typedef struct {
    u8 pad0[4];
    u8 id;
    u8 pad5;
    s16 x;
    u8 pad8[2];
    s16 z;
    u8 padC[0x14];
} Spot;

typedef struct {
    u8 pad0[0x4C];
    s32 count;
    Spot *spots;
} SpotTable;

extern SpotTable D_800A4F00;

Spot *func_8002AB64(s32 id, s16 *pos) {
    Spot *s;
    s32 i;
    s32 dx[2];
    s32 dz[2];

    if (id != -1) {
        s = D_800A4F00.spots;
        for (i = D_800A4F00.count; i > 0; i--, s++) {
            if (id == -2 || s->id == id) {
                do {
                    if (pos == NULL) {
                        return s;
                    }
                    dx[0] = pos[1] - s->x;
                    dz[0] = pos[5] - s->z;
                    if (dx[0] * dx[0] + dz[0] * dz[0] < 31250) {
                        return s;
                    }
                } while (0);
            }
        }
    }
    return NULL;
}
