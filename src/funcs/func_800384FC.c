#include "common.h"

extern s32 D_8008A618;
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008A654;
extern s32 D_8008B18C;
extern s32 func_80037BB8(void);
extern s32 func_800383E8(void);
extern s32 MemCardExist(s32);

s32 func_800384FC(s32 slot) {
    if (D_8008A618 == 0) {
        return 0;
    }
    if (slot == 0) {
        if (func_80037BB8() == 0) {
            return 1;
        }
        func_800383E8();
        if (D_8008B18C == 1 || D_8008B18C == 8) {
            return 0;
        }
        return 1;
    }
    D_8008A654 = slot;
    MemCardExist(D_8008A63C + D_8008A640);
    return 1;
}
