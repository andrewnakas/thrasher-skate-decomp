#include "common.h"

typedef struct {
    u8 pad0[0x61];
    u8 unk61;
    u8 pad62[0xE];
} Ent_800562A8;

extern u8 D_8008B4DC;
extern Ent_800562A8 D_800B2428[];

s32 func_800562A8(void) {
    s32 r = 0;

    switch (D_800B2428[D_8008B4DC].unk61) {
    case 0:
        r = 0;
        break;
    case 1:
    case 2:
    case 3:
        r = 1;
        break;
    case 4:
    case 5:
    case 6:
        r = 2;
        break;
    case 7:
    case 8:
    case 9:
        r = 3;
        break;
    case 10:
    case 11:
        r = 4;
        break;
    }
    return r;
}
