#include "common.h"

extern u8 D_8006F2BC[];

void func_8001DCF8(u8 *arg0, u32 arg1) {
    s32 *table;
    s32 v;

    if (*(u16 *)arg0 & 4) {
        table = *(s32 **)(arg0 + 0x24);
        v = table[arg1 & 0xFF];
        if (v == 0) {
            v = (s32)D_8006F2BC;
        }
    } else if ((arg1 & 0xFF) == 0) {
        v = *(s32 *)(arg0 + 0x24);
    } else {
        v = (s32)D_8006F2BC;
    }
    *(s32 *)(arg0 + 0x28) = v;
    *(u16 *)(arg0 + 0x2C) = 0;
    *(u8 *)(arg0 + 0x2E) = 0;
}
