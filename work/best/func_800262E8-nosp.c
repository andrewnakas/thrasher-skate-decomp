#include "common.h"

extern s32 D_8008AF24;
extern s32 D_8008AF28;

void func_80024720(void);
s32 GetSp(void);
void func_80023BA8(s32);
void func_80025B90(s32, s32);

void func_800262E8(s32 a0, s32 a1) {
    D_8008AF24 = a0;
    D_8008AF28 = a1;
    func_80024720();
    func_80023BA8(GetSp());
    func_80025B90(D_8008AF24, D_8008AF28);
    func_80023BA8(0);
}
