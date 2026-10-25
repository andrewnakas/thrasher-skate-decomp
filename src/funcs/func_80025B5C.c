#include "common.h"

extern s32 D_8008A2BC;
extern u8 D_8008AF54[8];

void func_80024720(void);

void func_80025B5C(void) {
    func_80024720();
    *(s32 *) (D_8008AF54 + D_8008A2BC * 4) = 0;
}
