#include "common.h"

extern u8 D_800A1C90[];

void func_8002B2B0(u8 *arg0, u8 *arg1) {
    u8 *e;
    u8 *slot;
    s32 i;

    slot = NULL;
    e = D_800A1C90 + *(u16 *) (arg0 + 0x2A) * 36;
    for (i = 7; i != -1; i--) {
        if (*(u8 **) (e + 4 + i * 4) == arg1) {
            return;
        }
        if (*(u8 **) (e + 4 + i * 4) == 0) {
            slot = e + 4 + i * 4;
        }
    }
    *(u8 **) slot = arg1;
    *(u16 *) (e + 2) = *(u16 *) (e + 2) + 1;
    for (i = 3; i != -1; i--) {
        if (*(u8 **) (arg1 + 0x34 + i * 4) == 0) {
            *(u8 **) (arg1 + 0x34 + i * 4) = arg0;
            *(s32 *) (arg1 + 0x44) = *(s32 *) (arg1 + 0x44) + 1;
            break;
        }
    }
}
