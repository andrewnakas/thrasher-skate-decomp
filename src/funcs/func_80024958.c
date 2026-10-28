#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

void func_80024958(u8 *c, u8 *seg, s32 *out) {
    Vec3i n;
    Vec3i d;
    s32 d1;
    s32 d2;
    s32 t;

    n.x = *(s32 *) (seg + 0x10);
    n.y = *(s32 *) (seg + 0x14);
    n.z = *(s32 *) (seg + 0x18);

    d.x = *(s16 *) (seg + 2) - *(s16 *) (c + 2);
    d.y = *(s16 *) (seg + 4) - *(s16 *) (c + 6);
    d.z = *(s16 *) (seg + 6) - *(s16 *) (c + 0xA);

    d1 = d.x * n.x + d.y * n.y + d.z * n.z;

    if (d1 < 0) {
        d.x = *(s16 *) (seg + 8) - *(s16 *) (c + 2);
        d.y = *(s16 *) (seg + 0xA) - *(s16 *) (c + 6);
        d.z = *(s16 *) (seg + 0xC) - *(s16 *) (c + 0xA);

        d2 = d.x * n.x + d.y * n.y + d.z * n.z;

        if (d2 > 0) {
            t = (d2 + 0x8000) >> 16;
            out[0] = (*(s16 *) (seg + 8) << 16) - n.x * t;
            out[1] = (*(s16 *) (seg + 0xA) << 16) - n.y * t;
            out[2] = (*(s16 *) (seg + 0xC) << 16) - n.z * t;
        } else {
            out[0] = *(s16 *) (seg + 8) << 16;
            out[1] = *(s16 *) (seg + 0xA) << 16;
            out[2] = *(s16 *) (seg + 0xC) << 16;
        }
    } else {
        out[0] = *(s16 *) (seg + 2) << 16;
        out[1] = *(s16 *) (seg + 4) << 16;
        out[2] = *(s16 *) (seg + 6) << 16;
    }
}
