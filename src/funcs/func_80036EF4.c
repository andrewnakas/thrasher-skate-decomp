#include "common.h"

typedef struct {
    u16 v;
    u8 pad2[6];
    u8 b[2];
} Swap80036EF4;

void func_80036EF4(u16 *p) {
    Swap80036EF4 s;

    s.v = *p;
    s.b[0] = ((u8 *) &s.v)[1];
    s.b[1] = ((u8 *) &s.v)[0];
    *p = *(u16 *) s.b;
}
