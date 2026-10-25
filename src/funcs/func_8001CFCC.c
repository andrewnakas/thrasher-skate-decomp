#include "common.h"

extern u8 *D_8008AEA0;
extern u8 *D_8008AE7C;
extern u8 *D_8008AE80;
extern u8 *D_8008AE84;
extern u8 *D_8008AE88;
extern u8 *func_8001C1DC(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e);
extern u8 *func_8001D428(u8 *a, u8 *b);
extern u8 *func_8001D5B0(u8 *a, u32 tag, s32 n);

s32 func_8001CFCC(void) {
    u8 *a;

    a = func_8001C1DC(D_8008AEA0, 0, 0, 0, 0);
    D_8008AE7C = a;
    a = func_8001D428(a, 0);
    D_8008AE80 = a;
    D_8008AE84 = func_8001D5B0(a, 0x44484D5A, 1);
    D_8008AE88 = func_8001D5B0(D_8008AE80, 0x50414D5A, 1);
    return 0;
}
