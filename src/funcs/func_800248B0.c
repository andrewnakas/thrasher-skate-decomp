#include "common.h"

extern s32 D_8008A2BC;
extern s32 D_8008AF6C[2];
extern s32 D_8008AF44[2];
extern s32 D_8008AF3C[2];
extern s32 D_8008AF34[2];

extern void func_80024720(s32, s32);
extern void func_80025544(s32, s32);
extern void func_80025004(s32, s32);

void func_800248B0(s32 a0, s32 a1) {
    func_80024720(a0, a1);
    if (!D_8008AF6C[D_8008A2BC]) {
        D_8008AF44[D_8008A2BC] = 1;
        if (D_8008AF3C[D_8008A2BC]) {
            func_80025544(a0, a1);
        }
        if (D_8008AF34[D_8008A2BC]) {
            func_80025004(a0, a1);
        }
    }
}
