#include "common.h"

extern u16 D_8008A7F4;
void func_8003EE18(void);
void func_8003C760(void);

s32 func_800464B0(void) {
    if (D_8008A7F4 != 0) {
        func_8003EE18();
        func_8003C760();
        D_8008A7F4 = 0;
    }
    return 1;
}
