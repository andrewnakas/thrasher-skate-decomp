#include "common.h"

extern u32 D_8008B240;
extern u32 D_8008B244;

void func_8003B6DC(u32 a, u32 b) {
    D_8008B240 = a;
    D_8008B244 = b;
}
