#include "common.h"

extern s32 D_8008AEAC;
extern u8 *D_8008AEB0;
extern void func_8001DB74(u8 *e);

void func_8001DBDC(u8 *filter) {
    s32 n = D_8008AEAC;
    u8 *e = D_8008AEB0;

    while (n > 0) {
        if ((*(u16 *) e & 1) != 0) {
            if (filter == 0 || *(u8 **) (e + 0x1C) == filter) {
                func_8001DB74(e);
            }
        }
        n--;
        e += 0x6C;
    }
}
