#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

extern Vec3i D_8008A348;
extern Vec3i D_8008A354;

s16 *func_8002E68C(u8 *obj, s16 *out) {
    Vec3i lo;
    Vec3i hi;
    s32 i;
    u8 *p;
    s16 *v;

    lo = D_8008A348;
    hi = D_8008A354;

    i = 2;
    if (*(u16 *) obj & 1) {
        i = 3;
    }

    if (i >= 0) {
        p = (u8 *) ((u32) (4 * i) + (u32) obj);
        do {
            v = *(s16 **) (p + 0x1C);
            lo.x = lo.x < v[0] ? lo.x : v[0];
            lo.y = lo.y < v[1] ? lo.y : v[1];
            lo.z = lo.z < v[2] ? lo.z : v[2];
            hi.x = hi.x > v[0] ? hi.x : v[0];
            hi.y = hi.y > v[1] ? hi.y : v[1];
            hi.z = hi.z > v[2] ? hi.z : v[2];
            p -= 4;
        } while (--i >= 0);
    }

    out[0] = (lo.x + hi.x) >> 1;
    out[3] = (u16) hi.x - out[0];
    out[1] = (lo.y + hi.y) >> 1;
    out[4] = (u16) hi.y - out[1];
    out[2] = (lo.z + hi.z) >> 1;
    out[5] = (u16) hi.z - out[2];

    return out;
}
