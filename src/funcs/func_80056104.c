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

u32 func_80056104(void) {
    u32 ret;

    switch (D_800B2428[D_8008B4DC].f61) {
    case 0:
        ret = D_800B2428[D_8008B4DC].f50 & 1;
        break;
    case 1:
    case 2:
    case 3:
        ret = 0;
        if ((D_800B2428[D_8008B4DC].f50 >> 1) & 1) {
            if ((D_800B2428[D_8008B4DC].f50 >> 2) & 1) {
                ret = (D_800B2428[D_8008B4DC].f50 >> 3) & 1;
            }
        }
        break;
    case 4:
    case 5:
    case 6:
        ret = 0;
        if ((D_800B2428[D_8008B4DC].f50 >> 4) & 1) {
            if ((D_800B2428[D_8008B4DC].f50 >> 5) & 1) {
                ret = (D_800B2428[D_8008B4DC].f50 >> 6) & 1;
            }
        }
        break;
    case 7:
    case 8:
    case 9:
        ret = 0;
        if ((D_800B2428[D_8008B4DC].f50 >> 7) & 1) {
            if ((D_800B2428[D_8008B4DC].f50 >> 8) & 1) {
                ret = (D_800B2428[D_8008B4DC].f50 >> 9) & 1;
            }
        }
        break;
    case 10:
    case 11:
        ret = 0;
        if ((D_800B2428[D_8008B4DC].f50 >> 10) & 1) {
            ret = (D_800B2428[D_8008B4DC].f50 >> 11) & 1;
        }
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}
