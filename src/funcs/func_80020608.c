#include "common.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
    u8 pad04[0x24];
    u8 b28;
    u8 pad29[3];
    s32 w2C;
} Node;

extern u8 D_8008AED4;
extern u8 D_8008A2AC;
extern Node D_80092C84[2][30];
extern Node D_800937C4[2][100];
extern Node D_80095D44[2][40];
extern Node D_80096C44[2][225];

s32 func_80020608(void) {
    s32 i;
    s32 j;
    s32 m1;

    D_8008AED4 = 0;
    D_8008A2AC = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 29; j++) {
            D_80092C84[i][j].addr = (u32) &D_80092C84[i][j + 1];
            m1 = -1;
        }
        for (j = 0; j < 30; j++) {
            D_80092C84[i][j].len = 0;
            D_80092C84[i][j].w2C = m1;
            D_80092C84[i][j].b28 = 0;
        }
        for (j = 0; j < 99; j++) {
            D_800937C4[i][j].addr = (u32) &D_800937C4[i][j + 1];
        }
        for (j = 0; j < 100; j++) {
            D_800937C4[i][j].len = 0;
            D_800937C4[i][j].w2C = -1;
            D_800937C4[i][j].b28 = 0;
        }
        for (j = 0; j < 39; j++) {
            D_80095D44[i][j].addr = (u32) &D_80095D44[i][j + 1];
        }
        for (j = 0; j < 40; j++) {
            D_80095D44[i][j].len = 0;
            D_80095D44[i][j].w2C = -1;
            D_80095D44[i][j].b28 = 0;
        }
        for (j = 0; j < 224; j++) {
            D_80096C44[i][j].addr = (u32) &D_80096C44[i][j + 1];
        }
        for (j = 0; j < 225; j++) {
            D_80096C44[i][j].len = 0;
            D_80096C44[i][j].w2C = -1;
            D_80096C44[i][j].b28 = 0;
        }
    }
    return 0;
}
