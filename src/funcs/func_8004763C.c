#include "common.h"

typedef struct {
    u16 w0;
    u16 w1;
    u16 w2;
    u16 w3;
    u16 w4;
    u16 w5;
    u16 w6;
    u16 w7;
} Rec_8004763C;

extern Rec_8004763C D_800AB794[];

s32 func_8004763C(u16 i) {
    s32 v;

    v = D_800AB794[i].w0 & 0x180;
    if (v == 0) {
        return 4;
    }
    if (v == 0x80) {
        return 8;
    }
    return 0x10;
}
