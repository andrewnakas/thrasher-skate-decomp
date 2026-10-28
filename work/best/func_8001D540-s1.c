#include "common.h"

s32 func_8001D540(u8 *list, s32 key, s32 skip) {
    u8 *p = *(u8 **) (list + 0x10);
    u8 *end = *(u8 **) (list + 0xC);

    if (skip == 0) {
        p = p + 8 + *(u32 *) (p + 4);
    }
    while (p < end) {
        if (*(s32 *) p == key) {
            *(u8 **) (list + 0x10) = p;
            return ((s32) p - *(s32 *) (list + 8)) >> 2;
        }
        p = p + 8 + *(u32 *) (p + 4);
    }
    return -1;
}
