#include "common.h"

extern void func_800421D8(u8 *a, s32 b, s32 c);
extern void func_800421FC(u8 *a, s32 b, s32 c);
extern void func_8003F9F0(u8 *a, u32 b);

void func_8001CDA4(u8 *a0, u32 *a1) {
    if (*a1 & 0x20000000) {
        func_800421D8(a0, -0x401, 0x400);
    }
    if (*a1 & 0x1000000) {
        func_800421D8(a0, -0x801, 0x800);
    }
    if (*a1 & 0x10000000) {
        func_800421FC(a0, -1, 2);
    }
    func_8003F9F0(a0, (*a1 >> 22) & 3);
}
