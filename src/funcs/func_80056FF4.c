#include "common.h"

typedef struct {
    u32 w[0x1C];
} Rec_80056FF4;

typedef struct {
    u8 pad0[0x4D0];
    s32 flags;
    Rec_80056FF4 rec[6];
} Tbl_80056FF4;

extern Tbl_80056FF4 D_800B2508;
extern u8 D_8008B4E0[4];
extern Rec_80056FF4 D_800B2428[];

s32 func_80056FF4(u8 idx) {
    Tbl_80056FF4 *t;
    Rec_80056FF4 *recs;
    u32 mask;

    if (idx >= 6) {
    fail:
        return 7;
    }
    t = &D_800B2508;
    mask = 1 << idx;
    if ((t->flags & mask) == 0) {
        goto fail;
    }
    recs = t->rec;
    {
        s32 slot = D_8008B4E0[-4];
        D_800B2428[slot] = recs[idx];
    }
    return 0;
}
