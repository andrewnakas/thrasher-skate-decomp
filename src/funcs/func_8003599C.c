#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Ent;

typedef struct {
    Ent e[4];
} Port;

extern Ent D_800A6294[];
extern u8 D_800A62F4[];
extern u8 D_800A6318[];
extern s32 D_8008B108;

void func_80035BC0(u8 *, s32);
void func_80035C14(u8 *, s32);
void func_80035C9C(u8 *, s32);
void func_80035D2C(u8 *, s32);

s32 func_8003599C(void) {
    u8 b1;
    u8 b2;
    u8 n1;
    u8 n2;
    s32 i;
    s32 port;

    port = 0;
    b1 = D_800A62F4[0];
    b2 = D_800A6318[0];
    D_8008B108 = 0;
    n1 = D_800A62F4[1] >> 4;
    n2 = D_800A6318[1] >> 4;
    for (i = 0; i < 4; i++) {
        D_800A6294[i + port * 4].b = -1;
    }
    if (!(b1 & 1)) {
        switch (n1) {
        case 4:
            func_80035BC0(D_800A62F4, port << 2);
            break;
        case 2:
            func_80035C14(D_800A62F4, port << 2);
            break;
        case 7:
            func_80035C9C(D_800A62F4, port << 2);
            break;
        case 8:
            func_80035D2C(D_800A62F4, port);
            break;
        default:
            ((Port *) D_800A6294)[port].e[0].b = 0;
            break;
        case 0:
            break;
        }
    }
    port = 1;
    for (i = 0; i < 4; i++) {
        D_800A6294[i + port * 4].b = -1;
    }
    if (!(b2 & 1)) {
        switch (n2) {
        case 4:
            func_80035BC0(D_800A6318, port << 2);
            break;
        case 2:
            func_80035C14(D_800A6318, port << 2);
            break;
        case 7:
            func_80035C9C(D_800A6318, port << 2);
            break;
        case 8:
            func_80035D2C(D_800A6318, port);
            break;
        default:
            ((Port *) D_800A6294)[port].e[0].b = 0;
            break;
        case 0:
            break;
        }
    }
    return 0;
}
