#include "common.h"

extern s32 D_80089F58;
extern u32 D_80089F5C;
extern s32 D_80089F60;
extern s32 func_8003682C(void);
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern u8 *func_80034C20(s32);
extern void func_800140EC(s32);

s32 func_80014058(void) {
    s32 i = 0;
    u32 n;

    D_80089F58 = func_8003682C();
    if (D_80089F58 == 0) {
        return 1;
    }
    for (; func_80036A78(D_80089F58, i, 0) == 0; i++) {
        n = func_80036B18(D_80089F58);
        if (n < D_80089F5C) {
            n = D_80089F5C;
        }
        D_80089F5C = n;
    }
    D_80089F60 = func_80034C20(D_80089F5C);
    func_800140EC(0);
    return 0;
}
