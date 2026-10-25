#include "common.h"

extern u32 D_8008B134;
extern u32 D_8008A598;
void printf(char *, ...);

void func_800379F4(void) {
    u32 i;

    i = 0;
    while (D_8008B134 != 0) {
        if (i++ > D_8008A598 * 10) {
            printf("Breaking out of zfileFlush - Should never happen\n");
            break;
        }
    }
}
