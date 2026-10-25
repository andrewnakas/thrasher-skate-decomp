#include "common.h"

extern s32 D_8008A2BC;
extern u8 D_8008AF4C[8];
extern u8 D_8008A2C0[8];

void func_80024720(void);

void func_80025A0C(s32 a0, s32 a1, u16 v) {
    s32 i;
    s32 j;

    func_80024720();
    i = D_8008A2BC;
    j = i * 2;
    *(s32 *) (D_8008AF4C + i * 4) = 1;
    *(u16 *) (D_8008A2C0 + j) = v;
}
