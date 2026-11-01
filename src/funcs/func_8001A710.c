#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 flags;          /* 0x04 */
    u8 pad8[4];
    s32 x;              /* 0x0C */
    s32 y;              /* 0x10 */
    s32 z;              /* 0x14 */
} Obj_8001A710;

typedef struct {
    Obj_8001A710 *obj;
    u8 pad4[0x14];
} Slot_8001A710;

extern Slot_8001A710 *func_8001A6F8(s32 *);

s32 func_8001A710(s32 *pos, s32 r) {
    s32 d[3];
    s32 n;
    s32 dist;
    Slot_8001A710 *s;
    Obj_8001A710 *o;

    s = func_8001A6F8(&n);
    while (--n != -1) {
        o = s->obj;
        if (o->flags & 1) {
            d[0] = abs((o->x - pos[0]) >> 16);
            d[2] = abs((o->z - pos[2]) >> 16);
            d[1] = abs((o->y - pos[1]) >> 16);
            dist = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
            if (dist < r) {
                return dist;
            }
        }
        s++;
    }
    return 0;
}
