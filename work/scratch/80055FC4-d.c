#include "common.h"

typedef struct {
    u8 pad00[0x14];
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    u8 pad44[0x1D];
    u8 f61;
} Rec;

extern u8 D_800B2428[];
extern u8 D_8008B4DC;

s32 func_80055FC4(void) {
    Rec *r;
    s32 v;

    r = (Rec *) ((u32) (112 * D_8008B4DC) + (u32) D_800B2428);

    v = r->f61;

    switch (v) {
    case 0:
        return r->f14;
    case 1:
        ;
    case 2:
        ;
    case 3:
        return r->f18 + r->f1C + r->f20;
    case 4:
    case 5:
    case 6:
        return r->f24 + r->f28 + r->f2C;
    case 7:
    case 8:
    case 9:
        return r->f30 + r->f34 + r->f38;
    case 10:
    case 11:
        return r->f3C + r->f40;
    }
    return 0;
}
