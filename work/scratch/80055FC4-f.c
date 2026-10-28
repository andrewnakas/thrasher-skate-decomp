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

extern Rec D_800B2428[];
extern u8 D_8008B4DC;

s32 func_80055FC4(void) {
    switch (D_800B2428[D_8008B4DC].f61) {
    case 0:
        return D_800B2428[D_8008B4DC].f14;
    case 1:
    case 2:
    case 3:
        return D_800B2428[D_8008B4DC].f18 + D_800B2428[D_8008B4DC].f1C + D_800B2428[D_8008B4DC].f20;
    case 4:
    case 5:
    case 6:
        return D_800B2428[D_8008B4DC].f24 + D_800B2428[D_8008B4DC].f28 + D_800B2428[D_8008B4DC].f2C;
    case 7:
    case 8:
    case 9:
        return D_800B2428[D_8008B4DC].f30 + D_800B2428[D_8008B4DC].f34 + D_800B2428[D_8008B4DC].f38;
    case 10:
    case 11:
        return D_800B2428[D_8008B4DC].f3C + D_800B2428[D_8008B4DC].f40;
    }
    return 0;
}
