#include "common.h"

extern u32 D_8008A6DC;
extern u32 D_8008A708;

void func_8003B8A0(u32 v) {
    D_8008A6DC = v;
    if (v == 1) {
        D_8008A708 = 0;
    } else {
        D_8008A708 = v;
    }
}
