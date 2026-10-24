#include "common.h"

extern u32 D_8008B1FC[2];
extern s32 D_8008B204;

void func_8003AAAC(u32 v) {
    s32 i;
    u32 *p;
    s32 n;

    i = 0;
    p = D_8008B1FC;
    while (i < 2) {
        if (*p == v) {
            n = D_8008B204;
            *p = 0;
            D_8008B204 = n - 1;
        }
        i++;
        p++;
    }
}
