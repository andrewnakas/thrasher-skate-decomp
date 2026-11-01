#include "common.h"

typedef struct {
    u8 pad0[0x28];
    u8 f28;
    u8 pad29[7];
} Rec;

extern u8 D_8008A2AC;

s32 func_80020C34(s32, u32, u8, Rec **, u32 *, s32 *);

s32 func_80020D74(u8 a, u8 b) {
    Rec *recs;
    u32 count;
    s32 sp20;
    u32 i;
    s32 key;

    func_80020C34(a, b, D_8008A2AC, &recs, &count, &sp20);
    key = a << 16;
    key |= b << 8;
    for (i = 0; i < count; i++) {
        if (recs[i].f28 == 0) {
            return key | i;
        }
    }
    return -1;
}
