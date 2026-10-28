#include "common.h"

extern u8 D_80092C84[];
extern u8 D_800937C4[];
extern u8 D_80095D44[];
extern u8 D_80096C44[];

s32 func_80020C34(u8 type, u8 sub, u8 idx, s32 **out, s32 *a5, s32 *a6) {
    switch (type) {
    case 0:
        switch (sub) {
        case 0:
            *out = (s32 *) (D_80092C84 + 1440 * idx);
            *a5 = 0x1E;
            *a6 = 0;
            break;
        case 1:
            *out = (s32 *) (D_800937C4 + 4800 * idx);
            *a5 = 0x64;
            *a6 = sub;
            break;
        }
        break;
    case 1:
        switch (sub) {
        case 0:
            *out = (s32 *) (D_80095D44 + 1920 * idx);
            *a5 = 0x28;
            *a6 = 2;
            break;
        case 1:
            *out = (s32 *) (D_80096C44 + 10800 * idx);
            *a5 = 0xE1;
            *a6 = 3;
            break;
        }
        break;
    }
    return 0;
}
