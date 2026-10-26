#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
} Pos;

u8 *func_8001A6F8(s32 *);

s32 func_8001A710(Pos *arg0, s32 arg1) {
    u8 *list;
    u8 *e;
    s32 n;
    s32 d[3];
    s32 t;
    s32 dist;

    list = func_8001A6F8(&n);
    while (--n != -1) {
        e = *(u8 **)list;
        if (*(u32 *)(e + 4) & 1) {
            t = *(s32 *)(e + 0xC) - arg0->f0;
            t = t >> 16;
            if (t < 0) {
                t = -t;
            }
            d[0] = t;
            t = *(s32 *)(e + 0x14) - arg0->f8;
            t = t >> 16;
            if (t < 0) {
                t = -t;
            }
            d[2] = t;
            t = *(s32 *)(e + 0x10) - arg0->f4;
            t = t >> 16;
            if (t < 0) {
                t = -t;
            }
            d[1] = t;
            dist = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
            if (dist < arg1) {
                return dist;
            }
        }
        list += 0x18;
    }
    return 0;
}
