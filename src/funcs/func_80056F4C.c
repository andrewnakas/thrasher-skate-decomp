#include "common.h"

typedef struct {
    u32 w[0x1C];
} Rec_80056F4C;

typedef struct {
    u8 pad0[0x4D0];
    s32 flags;
    Rec_80056F4C rec[6];
} Tbl_80056F4C;

extern Rec_80056F4C D_800B29DC[];
extern Rec_80056F4C D_800B2428[];
extern u8 D_8008B4E0[4];

s32 func_80056F4C(s32 slot) {
    Rec_80056F4C *recs;
    Tbl_80056F4C *t;

    if ((u8) slot >= 6) {
        return 7;
    }
    {
        s32 k = D_8008B4E0[-4];
        D_800B29DC[(u8) slot] = D_800B2428[k];
    }
    recs = D_800B29DC;
    t = (Tbl_80056F4C *) ((u8 *) recs - 0x4D4);
    t->flags |= 1 << slot;
    return 0;
}
