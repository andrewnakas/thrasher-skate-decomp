#include "common.h"

extern s32 D_8008A644;
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008B188;
extern s32 D_8008B190;
extern u8 D_800A81AC[];
s32 MemCardGetDirentry(s32, s32, void *, void *, s32, s32);

s32 func_80037C4C(s32 a0) {
    if (D_8008A644 == 0) {
        D_8008B188 = MemCardGetDirentry(D_8008A63C + D_8008A640, a0, D_800A81AC,
                                        &D_8008B190, 0, 0xF);
        if (D_8008B188 == 0) {
            D_8008A644 = 1;
            return 0;
        }
        return 1;
    }
    return 0;
}
