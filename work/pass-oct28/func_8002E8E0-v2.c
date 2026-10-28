#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 x1;  /* 0x02 */
    u8 pad4[2];
    s16 z1;  /* 0x06 */
    s16 x2;  /* 0x08 */
    u8 padA[2];
    s16 z2;  /* 0x0C */
    u8 padE[0xE];
} Seg_8002E8E0;

typedef struct {
    u8 pad0[0xC];
    Seg_8002E8E0 *seg; /* 0x0C */
    u8 pad10[0xE];
    u16 count;         /* 0x1E */
} Ent_8002E8E0;

extern Seg_8002E8E0 *D_800A4FF0[];
extern Ent_8002E8E0 **D_800A4F60[];
extern Ent_8002E8E0 **func_8002C1B4(u8 *, s32);

void func_8002E8E0(u8 *a0, s32 a1, s32 a2) {
    Ent_8002E8E0 **list;
    Ent_8002E8E0 **slot;
    Seg_8002E8E0 **out;
    Ent_8002E8E0 *ent;
    Seg_8002E8E0 *seg;
    s32 r2;
    s32 n;
    s32 k;
    s32 dx;
    s32 dz;
    slot = (Ent_8002E8E0 **) D_800A4F60;
    out = (Seg_8002E8E0 **) D_800A4FF0;
    r2 = (a2 >> 16) * (a2 >> 16);
    list = func_8002C1B4(a0, a2);
    while ((ent = *list++) != 0) {
        n = ent->count;
        for (k = 0; k < n; k++) {
            seg = ent->seg + k;
            dx = seg->x1 - *(s16 *) (a0 + 2);
            dz = seg->z1 - *(s16 *) (a0 + 0xA);
            if (r2 >= dx * dx + dz * dz) {
                *out = seg;
                *slot = out;
                out++;
                slot++;
            } else {
                dx = seg->x2 - *(s16 *) (a0 + 2);
                dz = seg->z2 - *(s16 *) (a0 + 0xA);
                if (r2 < dx * dx + dz * dz) {
                    continue;
                }
                *out = seg;
                *slot = out;
                out++;
                slot++;
            }
        }
    }
    *slot = 0;
}
