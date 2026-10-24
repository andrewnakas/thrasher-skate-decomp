#include "common.h"

extern s32 D_80089F58;
extern s32 D_80089F60;
extern s32 D_80089F64;
extern s32 D_8008AD14;
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern void func_80036BF4(s32, s32);
extern u8 *func_80014170(s32, s32, s32);

u8 *func_800140EC(u16 idx) {
    s32 r;

    if (idx == D_80089F64) {
        return (u8 *)&D_8008AD14;
    }
    if (func_80036A78(D_80089F58, idx, 0) != 0) {
        return NULL;
    }
    r = func_80036B18(D_80089F58);
    func_80036BF4(D_80089F58, D_80089F60);
    D_80089F64 = idx;
    return func_80014170(D_80089F60, r, 1);
}
