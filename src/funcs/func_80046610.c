#include "common.h"

typedef struct {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
} Quad_80046610;

extern Quad_80046610 D_800AB794[];

void func_80046610(u16 i, u16 j) {
    Quad_80046610 t;
    Quad_80046610 *base;
    Quad_80046610 *p;
    Quad_80046610 *q;

    base = D_800AB794;
    p = &base[i];
    q = &base[j];
    t = *p;
    *p = *q;
    *q = t;
}
