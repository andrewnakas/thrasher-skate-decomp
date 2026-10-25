#include "common.h"

extern s32 D_8008AE38;
extern s32 D_8008AE3C;
extern u8 *D_8008AE5C;
extern s32 D_8008AE60;
extern u8 D_8008AE70[8];
extern u8 D_8006E844[0x2D0];
extern u8 D_8006EB14[0x2F0];

void func_8001CE98(void);

s32 func_8001CE40(void) {
    D_8008AE38 = (s32) D_8006E844;
    D_8008AE3C = 0x2D0;
    func_8001CE98();
    D_8008AE5C = D_8006EB14;
    D_8008AE60 = 0x2F0;
    memset(D_8008AE70, 0, 0xC);
    return 0;
}
