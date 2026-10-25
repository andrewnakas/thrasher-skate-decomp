#include "common.h"

extern s32 D_8008A608;
extern s32 D_8008A60C;
extern s32 D_8008A610;
extern volatile u32 D_8008B144;

s32 func_80036324(void);

s32 func_80036F24(void) {
    D_8008A608 = 0;
    D_8008A60C = 0;
    D_8008A610 = 0;
    D_8008B144 = func_80036324();
    return 0;
}
