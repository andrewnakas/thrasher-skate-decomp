#include "common.h"

typedef struct {
    s32 f0;
    u8 f4;
    u8 f5;
    u8 pad6[2];
    u8 *f8;
    u16 fC;
    u8 padE[2];
} S_800347FC;

extern u8 D_8008B0CC[8];

void func_800347FC(u16 a, u8 *p, u8 b) {
    S_800347FC *s = (S_800347FC *) D_8008B0CC;

    s->f0 = 1;
    s->fC = a;
    s->f4 = b;
    s->f5 = *p;
    s->f8 = p + 4;
}
