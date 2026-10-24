#include "common.h"

extern u8 D_8008A714;
extern u8 D_8008A715;
extern u8 D_8008A716;
extern u8 D_8008234C[];

void func_8003B8C8(u8 a, u8 b, u8 c) {
    u8 *p;

    D_8008A714 = a;
    D_8008A715 = b;
    D_8008A716 = c;
    p = D_8008234C;
    p[0x19] = a;
    p[0x1A] = b;
    p[0x1B] = c;
    p[0x89] = a;
    p[0x8A] = b;
    p[0x8B] = c;
}
