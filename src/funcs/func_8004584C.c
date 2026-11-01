/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct PTag_8004584C {
    u32 addr : 24;
    u32 len : 8;
} PTag_8004584C;

typedef struct Prim_8004584C {
    PTag_8004584C tag;
    u32 code;
} Prim_8004584C;

typedef struct Ot_8004584C {
    u8 pad0[8];
    PTag_8004584C tag;
} Ot_8004584C;

extern Ot_8004584C *D_8008B3A0[];
extern Prim_8004584C *D_8008B3B0[];

void func_8004584C(s32 abr) {
    Prim_8004584C p;
    Prim_8004584C *prim;
    Ot_8004584C *ot;

    p.tag.len = 1;
    p.code = ((abr & 3) << 5) | 0xE1000600;
    *D_8008B3B0[-1] = p;
    prim = D_8008B3B0[-1];
    ot = D_8008B3A0[0];
    prim->tag.addr = ot->tag.addr;
    ot->tag.addr = (u32) prim;
    *(Prim_8004584C **) ((u8 *) D_8008B3B0 - 4) = prim + 1;
}
