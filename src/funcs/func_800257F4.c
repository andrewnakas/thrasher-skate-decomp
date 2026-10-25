#include "common.h"

extern s32 D_8008A2BC;
extern u8 D_8008AF64[8];

void func_80024720(void);

void func_800257F4(void) {
    func_80024720();
    *(s32 *) (D_8008AF64 + D_8008A2BC * 4) = 1;
}
