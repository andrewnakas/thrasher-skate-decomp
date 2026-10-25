#include "common.h"

extern s32 D_8008A360;
void func_8004FB00(s32 a0);
void func_8004D1B0(void);
void func_8004ABB0(void);
void func_8004DD38(void);

void func_800305F4(void) {
    func_8004FB00(0xFFFF);
    func_8004D1B0();
    func_8004ABB0();
    func_8004DD38();
    D_8008A360 = 0;
}
