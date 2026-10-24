#include "common.h"

extern s32 D_8008A618;
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008A644;
extern s32 D_8008B188;
extern s32 D_8008B18C;
extern s32 func_80037BB8(void);
extern s32 func_800383E8(void);
extern s32 MemCardFormat(s32);

s32 func_80038470(void) {
    if (D_8008A618 == 0) {
        return 1;
    }
    if (func_80037BB8() != 0) {
        func_800383E8();
        if (D_8008B18C != 0 && D_8008B18C != 4) {
            return 1;
        }
    }
    D_8008B188 = MemCardFormat(D_8008A63C + D_8008A640);
    func_800383E8();
    if (D_8008B18C != 0) {
        return 1;
    }
    D_8008A644 = 0;
    return 0;
}
