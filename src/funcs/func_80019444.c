#include "common.h"

extern u8 *D_8008AD6C;
extern u8 *D_8008AD70;

void *memset(void *dst, int c, u32 n);

u8 *func_80019444(void) {
    u8 *n = D_8008AD6C;

    if (n == 0) {
        return 0;
    }
    D_8008AD6C = *(u8 **) (n + 4);
    memset(n, 0, 0x10);
    *(u8 **) (n + 4) = D_8008AD70;
    D_8008AD70 = n;
    return n;
}
