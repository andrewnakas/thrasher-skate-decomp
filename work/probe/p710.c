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
    s32 dist;

    list = func_8001A6F8(&n);
    while (--n != -1) {
        e = *(u8 **)list;
        if (*(u32 *)(e + 4) & 1) {
            d[0] = *(s32 *)(e + 0xC) - arg0->f0;
            d[0] = d[0] >> 16;
            if (d[0] < 0) {
                d[0] = -d[0];
            }
            d[2] = *(s32 *)(e + 0x14) - arg0->f8;
            d[2] = d[2] >> 16;
            if (d[2] < 0) {
                d[2] = -d[2];
            }
            d[1] = *(s32 *)(e + 0x10) - arg0->f4;
            d[1] = d[1] >> 16;
            if (d[1] < 0) {
                d[1] = -d[1];
            }
            dist = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
            if (dist < arg1) {
                return dist;
            }
        }
        list += 0x18;
    }
    return 0;
}
