#include "common.h"

extern u32 D_8008B1FC[2];

void func_8003AA14(void) {
    s32 i;
    u32 *p;

    i = 0;
    p = D_8008B1FC;
    while (i < 2) {
        if (*p != 0) {
            ((void (*)(void)) *p)();
        }
        i++;
        p++;
    }
}
