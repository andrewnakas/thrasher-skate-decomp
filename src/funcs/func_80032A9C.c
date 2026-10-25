/* cflags: -mno-split-addresses */
#include "common.h"

extern u8 D_8008A6F4[0x10];
s32 func_80034C14(void);
s32 func_80036E6C(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_80032740(s32 a0);
void func_80034BD8(u32 a0);

void func_80032A9C(u16 v) {
    s32 t = func_80034C14();

    func_80032740(func_80036E6C(*(s32 *) D_8008A6F4, v, 0, 0));
    func_80034BD8(t);
}
