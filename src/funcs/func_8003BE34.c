/* a4 r5: func_8003B7F4 takes h in a0 (sra a0 feeds the final jal). */
#include "common.h"

typedef struct {
    u8 pad0[0x138];
    s16 h138;
    u8 pad13A[2];
    s32 w[6];
    s32 w154;
} Gfx3BE34;

extern s16 D_8008B274;
extern s32 D_800748C0[];
extern Gfx3BE34 D_8008234C;

s32 func_80032C54(s32, s32);
s32 func_80032C28(s32, s32);
s32 func_80032CF4(s32);
void func_8003B7F4(s32);

void func_8003BE34(s16 a) {
    s32 t;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 h;
    Gfx3BE34 *p;

    if (D_8008B274 == a) {
        return;
    }
    D_8008B274 = a;
    t = func_80032C54(0x1000000, D_800748C0[(u16) a >> 4]);
    b = func_80032C54(0x1000000, t);
    c = func_80032C54(0xF00000, t);
    d = func_80032C54(0x10000, b);
    e = func_80032C54(0x10000, c);
    f = func_80032CF4(func_80032C28(b, b) + 0x10000);
    g = func_80032CF4(func_80032C28(c, c) + 0x10000);
    h = t >> 16;
    p = &D_8008234C;
    p->w[0] = t >> 4;
    p->h138 = h;
    p->w[1] = b >> 4;
    p->w[2] = c >> 4;
    p->w[3] = d >> 4;
    p->w[4] = e >> 4;
    p->w[5] = f >> 4;
    p->w154 = g >> 4;
    func_8003B7F4(h);
}
