#include "common.h"

extern s32 D_8008B198;
extern void func_80059D88(s32);
extern void VSync(s32);
extern void func_8003A094(void);
extern void func_80034BD8(s32);

void func_80038784(void) {
    func_80059D88(0);
    VSync(0);
    func_8003A094();
    func_80034BD8(D_8008B198);
}
