#include "common.h"

extern void func_8003B5D8(s32 x, s32 y);
extern void func_8003B7C0(u8 r, u8 g, u8 b);
extern void func_8003B6EC(s32 a, s32 b);

void func_8003AECC(void) {
    func_8003B5D8(0x100, 0x78);
    func_8003B7C0(0, 0, 0);
    func_8003B6EC(0xED8, 0x1068);
}
