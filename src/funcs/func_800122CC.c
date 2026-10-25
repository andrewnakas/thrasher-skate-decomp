#include "common.h"

typedef struct {
    u32 f0;
    u32 f4;
    u8 pad8[0x18];
    s32 f20;
    s32 f24;
    s32 f28;
} S_800122CC;

void func_800122CC(S_800122CC *p, s32 *src) {
    s32 v[3];

    v[0] = src[0];
    v[1] = src[1];
    v[2] = src[2];
    switch (p->f0) {
    case 1:
    case 3:
        if (v[0] == 0x10000 && v[1] == v[0] && v[2] == v[1]) {
            p->f4 &= ~8;
        } else {
            p->f4 |= 8;
        }
        p->f20 = v[0];
        break;
    case 8:
        p->f20 = v[0];
        break;
    default:
        return;
    }
    p->f24 = v[1];
    p->f28 = v[2];
}
