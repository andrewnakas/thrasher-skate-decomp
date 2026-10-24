#include "common.h"

extern u32 D_8008B204;
extern u32 D_8008B200[2];

void func_8003A9F0(void) {
    s32 i;
    u32 *p;

    D_8008B204 = 0;
    i = 1;
    p = D_8008B200;
    do {
        *p = 0;
        p--;
        i--;
    } while (i >= 0);
}
