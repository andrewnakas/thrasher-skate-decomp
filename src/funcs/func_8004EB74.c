#include "common.h"

typedef struct {
    u32 mask;
    s32 mode;
    s16 depth_left;
    s16 depth_right;
} ReverbAttr_8004EB74;

typedef struct {
    s32 busy;
    u8 type;
    u8 depth;
} Cfg_8004EB74;

extern char D_80010848[];
extern char D_80010870[];
extern s32 D_80082940[];
extern u8 D_8008294C[];
extern ReverbAttr_8004EB74 D_8008298C;

s32 SpuClearReverbWorkArea(s32);
s32 SpuReserveReverbWorkArea(s32);
s32 SpuSetReverb(s32);
s32 SpuSetReverbModeParam(ReverbAttr_8004EB74 *);

s32 func_8004EB74(Cfg_8004EB74 *cfg) {
    s32 mode;

    if (cfg->busy == 0) {
        D_8008298C.mask = 1;
        switch (cfg->type) {
            case 0:
                mode = 0;
                D_80082940[0] = 0;
                break;
            case 1:
                mode = 3;
                D_80082940[0] = 0x4840;
                break;
            case 2:
                mode = 5;
                D_80082940[0] = 0xADE0;
                break;
            default:
                printf(D_80010848, D_80010870, 0x312);
                exit(1);
                break;
        }
        if (mode != D_8008298C.mode) {
            if (SpuReserveReverbWorkArea(0) != 0) {
                printf(D_80010848, D_80010870, 0x317);
                exit(1);
            }
            D_8008298C.mode = mode;
            if (SpuSetReverbModeParam(&D_8008298C) != 0) {
                printf(D_80010848, D_80010870, 0x31B);
                exit(1);
            }
            if (SpuClearReverbWorkArea(D_8008298C.mode) != 0) {
                printf(D_80010848, D_80010870, 0x31E);
                exit(1);
            }
            if (SpuReserveReverbWorkArea(1) != 1) {
                printf(D_80010848, D_80010870, 0x321);
                exit(1);
            }
        }
        D_8008294C[0] = cfg->depth;
        if (D_8008294C[0] != 0) {
            D_8008298C.mask = 6;
            D_8008298C.depth_left = D_8008294C[0] << 7;
            D_8008298C.depth_right = D_8008294C[0] << 7;
            if (SpuSetReverbModeParam(&D_8008298C) != 0) {
                printf(D_80010848, D_80010870, 0x328);
                exit(1);
            }
            if (SpuSetReverb(1) != 1) {
                printf(D_80010848, D_80010870, 0x32A);
                exit(1);
            } else {
                return 0;
            }
        }
        if (SpuSetReverb(0) != 0) {
            printf(D_80010848, D_80010870, 0x32D);
            exit(1);
        } else {
            return 0;
        }
    }
    printf(D_80010848, D_80010870, 0x331);
    exit(1);
}
