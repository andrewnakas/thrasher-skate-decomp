#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} VEC_80013BA8;

void func_80013BA8(VEC_80013BA8 *a, VEC_80013BA8 *b, VEC_80013BA8 *out, s32 n) {
    s32 d;

    do {
        d = a->x - b->x;
        if (d < 0) {
            d = -d;
        }
        if (d <= 0x7FFF) {
            out->x = (a->x + b->x + b->x * 2) >> 2;
        } else {
            out->x = ((u32)(u16)a->x + (u32)(u16)b->x + (u32)(u16)b->x + (u32)(u16)b->x) >> 2;
        }
        d = a->y - b->y;
        if (d < 0) {
            d = -d;
        }
        if (d <= 0x7FFF) {
            out->y = (a->y + b->y + b->y * 2) >> 2;
        } else {
            out->y = ((u32)(u16)a->y + (u32)(u16)b->y + (u32)(u16)b->y + (u32)(u16)b->y) >> 2;
        }
        d = a->z - b->z;
        if (d < 0) {
            d = -d;
        }
        if (d <= 0x7FFF) {
            out->z = (a->z + b->z + b->z * 2) >> 2;
        } else {
            out->z = ((u32)(u16)a->z + (u32)(u16)b->z + (u32)(u16)b->z + (u32)(u16)b->z) >> 2;
        }
        a++;
        b++;
        out++;
    } while (--n);
}
