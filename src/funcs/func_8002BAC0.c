#include "common.h"

typedef struct {
    u8 pad[0x58];
    s32 base;
    s32 count;
} S_8002BAC0;

extern u8 D_800A4F00[0x60];

s32 func_8002BAC0(u16 idx) {
    S_8002BAC0 *s = (S_8002BAC0 *) D_800A4F00;

    if (idx >= s->count) {
        idx = 0;
    }
    return s->base + idx * 0x38;
}
