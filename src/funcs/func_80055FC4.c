#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u32 f14;
    u32 f18;
    u32 f1C;
    u32 f20;
    u32 f24;
    u32 f28;
    u32 f2C;
    u32 f30;
    u32 f34;
    u32 f38;
    u32 f3C;
    u32 f40;
    u8 pad44[0x50 - 0x44];
    u32 f50;
    u8 pad54[0x61 - 0x54];
    u8 f61;
    u8 pad62[0x70 - 0x62];
} Rec;

extern Rec D_800B2428[];
extern u8 D_8008B4DC;

u32 func_80055FC4(void) {
    u32 ret = 0;

    switch (D_800B2428[D_8008B4DC].f61) {
    case 0:
        ret = D_800B2428[D_8008B4DC].f14;
        break;
    case 1:
    case 2:
    case 3:
        ret = D_800B2428[D_8008B4DC].f18 + D_800B2428[D_8008B4DC].f1C +
              D_800B2428[D_8008B4DC].f20;
        break;
    case 4:
    case 5:
    case 6:
        ret = D_800B2428[D_8008B4DC].f24 + D_800B2428[D_8008B4DC].f28 +
              D_800B2428[D_8008B4DC].f2C;
        break;
    case 7:
    case 8:
    case 9:
        ret = D_800B2428[D_8008B4DC].f30 + D_800B2428[D_8008B4DC].f34 +
              D_800B2428[D_8008B4DC].f38;
        break;
    case 10:
    case 11:
        ret = D_800B2428[D_8008B4DC].f3C + D_800B2428[D_8008B4DC].f40;
        break;
    }
    return ret;
}
