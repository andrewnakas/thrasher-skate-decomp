#include "common.h"

typedef struct {
    u8 pad0[3];
    u8 f3;
    u8 pad4[3];
    u8 f7;
    u8 pad8[0x20];
    u8 f28;
    u8 f29;
    u8 pad2A[6];
} Rec;

extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

s32 func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

s32 func_80020E10(u32 arg0, s32 arg1) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    u32 i;
    u32 k;

    if (arg0 != 0xFFFFFFFFU) {
        func_80020C34((arg0 >> 16) & 0xFF, (arg0 & 0xFF00) >> 8, D_8008A2AC, &sp18, &sp1C, &sp20);
        if (arg1 != 0) {
            switch (((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f28) {
            case 2:
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f3 = 9;
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f7 = 0x2C;
                break;
            case 3:
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f3 = 5;
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f7 = 0x28;
                if (((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f29 != 0) {
                    ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f7 |= 2;
                }
                break;
            case 4:
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f3 = 8;
                ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f7 = 0x38;
                if (((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f29 != 0) {
                    ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f7 |= 2;
                }
                break;
            case 0:
            case 1:
            case 5:
                break;
            }
        } else {
            ((Rec *) ((arg0 & 0xFF) * 0x30 + sp18))->f3 = 0;
        }
        D_8009C0A4[D_8008A2A4++] = arg0;
        for (i = 0; i < D_8008A2A8; i++) {
            if (D_8009C6D4[i] == arg0) {
                D_8008A2A8 -= 1;
                for (k = i; k < D_8008A2A8; k++) {
                    D_8009C6D4[k] = D_8009C6D4[k + 1];
                }
            }
        }
    }
    return 0;
}
