#include "common.h"

extern u8 D_800A1C90[];

void func_8002B360(u8 *arg0, u8 *arg1) {
    u8 *e;
    s32 i;

    e = D_800A1C90 + *(u16 *) (arg0 + 0x2A) * 36;
    for (i = 7; i != -1; i--) {
        if (*(u8 **) (e + 4 + i * 4) == arg1) {
            *(u8 **) (e + 4 + i * 4) = 0;
            *(u16 *) (e + 2) = *(u16 *) (e + 2) - 1;
            break;
        }
    }
    for (i = 3; i != -1; i--) {
        if (*(u8 **) (arg1 + 0x34 + i * 4) == arg0) {
            *(u8 **) (arg1 + 0x34 + i * 4) = 0;
            *(s32 *) (arg1 + 0x44) = *(s32 *) (arg1 + 0x44) - 1;
            break;
        }
    }
}
