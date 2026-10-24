#include "common.h"

extern u8 D_8008B238;
extern u8 D_8008B239;
extern u8 D_8008B23A;
extern void SetFarColor(u8 r, u8 g, u8 b);

void func_8003B7C0(u8 r, u8 g, u8 b) {
    D_8008B238 = r;
    D_8008B239 = g;
    D_8008B23A = b;
    SetFarColor(r, g, b);
}
