#include "common.h"

extern u32 D_8008A70C;
extern u32 D_8008A754;

void func_8003B9F8(u32 v) {
    if (D_8008A70C != 0) {
        D_8008A754 = v;
    }
}
