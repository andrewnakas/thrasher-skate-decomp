#include "common.h"

extern u16 D_8008A7F4;
void func_8003C758(void);
void func_8003ED28(void);

s32 func_80046478(void) {
    if (D_8008A7F4 == 0) {
        func_8003C758();
        func_8003ED28();
        D_8008A7F4 = 1;
    }
    return 1;
}
