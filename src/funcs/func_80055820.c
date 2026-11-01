#include "common.h"

void func_8001A078(void);
void func_800309C4(s32, s32, s32, s32, s32);
void func_80057530(void);
void func_800C29CC(void);
void func_800C3B98();
void func_800D2358(s32);
void func_800DA7F4(void);
void func_800DC774(void);
extern u8 D_8008B4D8[];
extern u8 D_800D234C[];

void func_80055820(void) {
    if (D_800D234C != NULL) {
        func_800D2358(0);
    }
    /* called without args: a0 = 1000 only via the delay slot of the branch */
    if (D_8008B4D8[0] != 0) {
        func_800C3B98();
    }
    func_800309C4(1000, 0, 0, 0, 0);
    func_800DC774();
    func_800C29CC();
    func_80057530();
    func_800DA7F4();
    func_8001A078();
}
