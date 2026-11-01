#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect3A09C;

extern Rect3A09C D_800A8404[256];

s32 func_800484B4(s16 a0, s32 a1, s32 a2, Rect3A09C *r);

u8 func_8003A09C(s16 a0, s32 a1, s32 a2, Rect3A09C *r) {
    s32 slot = -1;
    s32 i;

    for (i = 1; i < 256; i++) {
        if (D_800A8404[i].w == 0) {
            slot = i;
            break;
        }
    }
    if (slot == -1) {
    fail:
        return 0;
    }
    if (func_800484B4(a0, a1, a2, r) == 0) {
        goto fail;
    }
    D_800A8404[slot].x = r->x;
    D_800A8404[slot].y = r->y;
    D_800A8404[slot].w = r->w;
    D_800A8404[slot].h = r->h;
    return slot;
}
