#include "common.h"

extern u32 D_8008A75C;
extern u32 D_8008A760;
extern u32 D_8008A764;

void func_8003BB08(u32 a, u32 b, u32 c) {
    D_8008A75C = a;
    D_8008A760 = b;
    D_8008A764 = c;
}
