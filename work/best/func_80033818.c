#include "common.h"

typedef struct { u32 f00; u32 f04; u32 f08; u32 f0C; u32 f10; u32 f14; u32 f18; u32 f1C; } Rec;

void func_80033818(Rec *r) {
    u32 a = r->f04;
    u32 b = r->f0C;
    u32 c = r->f08;
    u32 d = r->f18;
    u32 e = r->f14;
    u32 f = r->f1C;

    r->f0C = a;
    r->f04 = b;
    r->f18 = c;
    r->f08 = d;
    r->f1C = e;
    r->f14 = f;
}
