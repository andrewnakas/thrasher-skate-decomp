#include "common.h"

extern u8 D_800A6294[];
extern u8 D_800A62F4[];
extern u8 D_800A6318[];
extern u32 D_8008B108;

void func_80035BC0(u8 *, s32);
void func_80035C14(u8 *, s32);
void func_80035C9C(u8 *, s32);
void func_80035D2C(u8 *);

s32 func_8003599C(void) {
    u8 *p1 = D_800A62F4;
    u8 *p2 = D_800A6318;
    u8 b1;
    u8 b2;
    u8 n1;
    u8 n2;
    s32 i;
    s32 k;
    s32 v;
    s32 z;

    v = 0;
    z = 0;
    b1 = p1[0];
    b2 = p2[0];
    D_8008B108 = 0;
    n1 = p1[1] >> 4;
    n2 = p2[1] >> 4;
    for (i = 0; i < 4; i++) {
        *(s32 *) (D_800A6294 + (i + z) * 12 + 4) = -1;
    }
    if ((b1 & 1) == 0) {
        k = n1;
        switch (k & 0xFF) {
        case 4:
            func_80035BC0(D_800A62F4, v << 2);
            break;
        case 2:
            func_80035C14(D_800A62F4, v << 2);
            break;
        case 7:
            func_80035C9C(D_800A62F4, v << 2);
            break;
        case 8:
            func_80035D2C(D_800A62F4);
            break;
        default:
            *(s32 *) (D_800A6294 + v * 0x30 + 4) = 0;
            break;
        case 0:
            break;
        }
    }
    v = 1;
    for (i = 0; i < 4; i++) {
        *(s32 *) (D_800A6294 + (i + 4) * 12 + 4) = -1;
    }
    if ((b2 & 1) == 0) {
        k = n2;
        switch (k & 0xFF) {
        case 4:
            func_80035BC0(D_800A6318, v << 2);
            break;
        case 2:
            func_80035C14(D_800A6318, v << 2);
            break;
        case 7:
            func_80035C9C(D_800A6318, v << 2);
            break;
        case 8:
            func_80035D2C(D_800A6318);
            break;
        default:
            *(s32 *) (D_800A6294 + v * 0x30 + 4) = 0;
            break;
        case 0:
            break;
        }
    }
    return 0;
}
