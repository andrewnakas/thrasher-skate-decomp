#include "common.h"

extern u8 *D_8008AD70;
extern u16 D_8008AD60;

void func_80019210(u8 *);
void func_80016D00(void);
s32 func_80015F9C(void);
void func_800387C0(void);

void func_80016C50(void) {
    u8 *p = D_8008AD70;

    while (p != 0) {
        u8 *next = *(u8 **)(p + 4);

        if ((*(u16 *)(p + 2) & 1) == 0) {
            func_80019210(p);
        }
        p = next;
    }
    D_8008AD60 = 0xC101;
    func_80016D00();
    if (func_80015F9C() == 0) {
        func_800387C0();
    }
}
