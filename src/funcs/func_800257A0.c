#include "common.h"

void func_800257A0(u8 *base) {
    u32 i;
    u8 *e;

    i = 0;
    while (i < *(u32 *) base) {
        e = base + i * 0x8C;
        if ((*(u16 *) (e + 6) & 1) != 0) {
            *(u16 *) (e + 4) = 0;
            *(u32 *) (e + 0x6C) = 0;
            *(u32 *) (e + 0x70) = 0;
            *(u32 *) (e + 0x74) = 0;
        }
        i++;
    }
}
