#include "common.h"

extern s32 D_8008A2BC;
extern u8 D_8008AF5C[8];

void func_80024720(void);

void func_800256F4(void) {
    func_80024720();
    *(s32 *) (D_8008AF5C + D_8008A2BC * 4) = 1;
}
