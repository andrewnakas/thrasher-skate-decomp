#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 f00[4];
    u32 flags;
    u8 f08[4];
    s32 x;
    s32 y;
    s32 z;
} Ent;

typedef struct {
    Ent *e;
    u8 pad[0x14];
} Slot;

s32 *func_8001A6F8(s32 *);

s32 func_8001A710(Vec3 *pos, s32 limit) {
    s32 n;
    Slot *slot;
    Ent *e;
    s32 d[3];
    s32 sum;

    slot = (Slot *) func_8001A6F8(&n);

    for (n = n - 1; n != -1; n--) {
        e = slot->e;
        if (e->flags & 1) {
            d[0] = (e->x - pos->x) >> 16;
            if (d[0] < 0) {
                d[0] = -d[0];
            }
            d[2] = (e->z - pos->z) >> 16;
            if (d[2] < 0) {
                d[2] = -d[2];
            }
            d[1] = (e->y - pos->y) >> 16;
            if (d[1] < 0) {
                d[1] = -d[1];
            }
            sum = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
            if (sum < limit) {
                return sum;
            }
        }
        slot++;
    }

    return 0;
}
