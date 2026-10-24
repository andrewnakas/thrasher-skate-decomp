#include "common.h"

extern void func_800498FC(u32 r, u32 g, u32 b, u16 a, u16 b2);

void func_8003A3C4(u32 v, u16 a, u16 b) {
    func_800498FC((v >> 8) & 0xFF, (v >> 16) & 0xFF, v >> 24, a, b);
}
