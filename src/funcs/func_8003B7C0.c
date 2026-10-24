#include "common.h"

extern u8 D_8008B238;
extern u8 D_8008B239;
extern u8 D_8008B23A;
extern void SetFarColor(u8 a0, u8 a1, u8 a2);

void func_8003B7C0(s32 a0, s32 a1, s32 a2) {
    D_8008B238 = a0;
    D_8008B239 = a1;
    D_8008B23A = a2;
    SetFarColor(a0, a1, a2);
}
