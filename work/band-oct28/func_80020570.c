#include "common.h"

extern u8 *func_800204F4(s32);
extern s32 func_8002050C(s32, s32);

s32 func_80020570(s32 a0, u8 *a1, s32 a2) {
    u8 *t;
    u8 *p;
    s32 acc;
    s32 c;

    t = func_800204F4(a0);
    acc = -a2;
    p = a1;
    for (c = *p++; c != 0; c = *p++) {
        acc += *(s32 *) (*(s32 *) (t + 8) + ((func_8002050C(a0, c & 0xFF) & 0xFF) << 4)
            + 0xC) + a2;
    }
    return acc;
}
