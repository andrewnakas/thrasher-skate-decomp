#include "common.h"

extern u32 D_8008A6A0[];
extern u32 D_8008B1A8;
extern void func_8003A5A4(u32 *p);

s32 func_8003A578(void) {
    func_8003A5A4(D_8008A6A0);
    D_8008B1A8 = 1;
    return 0;
}
