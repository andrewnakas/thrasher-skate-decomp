#include "common.h"

extern u8 *D_8008AE9C;
extern u8 *D_8008AE8C;
extern u8 *D_8008AE90;
extern u8 *func_8001C1DC(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e);
extern void func_8001D3B4(u32 key, u32 val);
extern u8 *func_8001D428(u8 *a, u8 *b);
extern s32 func_8001D540(u8 *a, u32 key, s32 flag);
extern void func_8001D620(u8 *a);
extern void func_8001D15C(void);

s32 func_8001D0E4(void) {
    u8 *a;

    a = func_8001C1DC(D_8008AE9C, (u8 *) 1, 0, 0, 0);
    D_8008AE8C = a;
    func_8001D3B4(0x44484C50, (u32) func_8001D15C);
    a = func_8001D428(D_8008AE8C, 0);
    D_8008AE90 = a;
    func_8001D540(a, 0x44484C50, 1);
    func_8001D620(D_8008AE90);
    return 0;
}
