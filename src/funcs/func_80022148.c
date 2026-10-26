#include "common.h"

void func_80032FE0(void *);

s32 func_80022148(s32 *arg0, u16 *arg1) {
    u8 *e;
    u16 h;

    e = (u8 *)((s32)arg0 + 4 + *arg0 * 140);
    h = arg1[0];
    *(u16 *)e = h;
    switch (h) {
    case 0:
    case 1:
    case 2:
        *(s32 *)(e + 0x34) = *(s32 *)(arg1 + 8);
        *(s32 *)(e + 0x3C) = *(s32 *)(arg1 + 10);
        *(s32 *)(e + 0x40) = *(s32 *)(arg1 + 12);
        *(s32 *)(e + 0x44) = *(s32 *)(arg1 + 2);
        *(s32 *)(e + 0x48) = *(s32 *)(arg1 + 4);
        *(s32 *)(e + 0x4C) = *(s32 *)(arg1 + 6);
        *(u16 *)(e + 2) = 0;
        func_80032FE0(e + 0x5C);
        func_80032FE0(e + 0x68);
        return (*arg0)++;
    default:
        return -1;
    }
}
