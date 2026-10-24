#include "common.h"

extern s32 D_8008A8C0;
extern s32 D_8008B3E4;
extern u8 D_8008A8C4[4];
extern u8 D_800AE794[];

void func_800484B4(s32, s32, s32, u8 *);

s32 func_80048450(void) {
    u16 *p;
    s32 i;

    D_8008A8C0 = 1;
    i = 0xFF;
    p = (u16 *) D_800AE794;
    p += 0xFF;
    for (; i >= 0; i--) {
        *p-- = 0;
    }
    func_800484B4(0x100, 0, 0, D_8008A8C4);
    D_8008B3E4 = 0;
    return 0;
}
