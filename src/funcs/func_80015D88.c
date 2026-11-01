#include "common.h"

extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;
extern u8 *D_8008AD40;
extern u8 *D_8008AD4C;
extern s32 D_8008AD50;

extern void func_80016204(u8 *p);
extern void func_800161DC(u8 *p);

s32 func_80015D88(void) {
    u8 *p;
    u8 *e;
    s32 i;
    s32 one;

    i = 0;
    one = 1;
    D_8008AD50 = 0;
    do {
        i++;
        p = D_8008AD38 - (i << 4);
        if ((u32) p < (u32) D_8008AD3C) {
            if ((u32) D_8008AD40 < (u32) (D_8008AD3C - 0x10)) {
                e = D_8008AD4C;
                if (e == (u8 *) -1) {
                    return 0;
                }
                func_80016204(e);
                while (*(u8 **) (e + 4) != 0) {
                    e = *(u8 **) (e + 4);
                }
                if (*(u32 *) (e + 8) < 0x11) {
                fail:
                    return 0;
                }
                *(u32 *) (e + 8) -= 0x10;
                func_800161DC(e);
                D_8008AD50 = one;
                D_8008AD3C -= 0x10;
                return i;
            }
            goto fail;
        }
    } while (*p == one);
    return i;
}
