#include "common.h"

extern s32 D_8008A1D8;
extern u8 *D_8008AEB0;
extern u8 *D_8008AEB8;
extern s32 D_8008AEAC;
extern s32 D_8008AEB4;
extern s32 D_8008AEC0;
extern s32 D_8008AEC8;
extern u8 *func_80034C20(u32);
extern void func_8001FF5C(void);

s32 func_8001D6D8(s32 a0, s32 a1) {
    u32 n;

    if (D_8008A1D8 != 0) {
        return 0;
    }
    n = a0 * 108;
    D_8008AEB0 = func_80034C20(n);
    if (D_8008AEB0 == 0) {
        return 1;
    }
    D_8008AEAC = a0;
    memset(D_8008AEB0, 0, n);
    n = a1 * 48;
    D_8008AEB8 = func_80034C20(n);
    if (D_8008AEB8 == 0) {
        return 1;
    }
    D_8008AEB4 = a1;
    memset(D_8008AEB8, 0, n);
    func_8001FF5C();
    D_8008AEC0 = 0;
    D_8008AEC8 = 0;
    D_8008A1D8 = 1;
    return 0;
}
