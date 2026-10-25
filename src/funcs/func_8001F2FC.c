#include "common.h"

extern s32 func_8001E900(u8 *self, u8 *e);

void func_8001F2FC(u8 *self) {
    u8 *p = *(u8 **) (self + 0x24);

    while (p != 0) {
        if (func_8001E900(self, p) != 0) {
            break;
        }
        p = *(u8 **) p;
    }
    if ((*(u8 *) (self + 0x5C) & 2) != 0) {
        *(u8 *) (*(u8 **) (self + 0x60) + 0x4C) = 0;
    }
}
