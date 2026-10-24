#include "common.h"

extern void (*D_8008B1FC[2])(void);

void func_8003AA14(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8008B1FC[i]) {
            D_8008B1FC[i]();
        }
    }
}
