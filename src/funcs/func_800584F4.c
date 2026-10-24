#include "common.h"

extern void func_800309C4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8001A078(void);
extern void func_800BB45C(void);
extern void func_80057530(void);

void func_800584F4(void) {
    func_800309C4(0x3E8, 0, 0, 0, 0);
    func_8001A078();
    func_800BB45C();
    func_80057530();
}
