#include "common.h"

extern u8 D_8008234C[];
extern s32 D_8008A710;
extern void func_8003B3CC(void);
extern void func_80059D88(s32 a0);
extern void VSync(s32 a0);
extern void func_8005A268(s32 a0);
extern void func_8005A174(s32 a0);

void func_8003B418(s32 a0) {
    u8 *p;

    func_8003B3CC();

    if (a0 != 0) {
        func_80059D88(0);
        VSync(0);
    }

    p = D_8008234C;
    func_8005A268(*(s32 *) (p + 0xE4) + 0x5C);
    func_8005A174(*(s32 *) (p + 0xE4));
    D_8008A710 = 0;
}
