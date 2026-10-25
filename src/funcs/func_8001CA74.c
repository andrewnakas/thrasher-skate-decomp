#include "common.h"

extern u8 *D_8008AE40;
extern u8 *D_8008AE44;

void func_8001CA74(void) {
    u8 *p = D_8008AE40;
    u8 *end = D_8008AE44;

    while (p < end) {
        *(u16 *) (p + 4) = 0xFFFF;
        p += 0xC;
    }
}
