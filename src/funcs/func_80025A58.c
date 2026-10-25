#include "common.h"

extern s32 D_8008A2BC;
extern u8 D_8008AF4C[8];

void func_80024720(void);

void func_80025A58(void) {
    func_80024720();
    *(s32 *) (D_8008AF4C + D_8008A2BC * 4) = 0;
}
