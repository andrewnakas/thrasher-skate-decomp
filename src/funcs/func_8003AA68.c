#include "common.h"

extern u32 D_8008B1FC[2];
extern s32 D_8008B204;

s32 func_8003AA68(u32 v) {
    s32 i;
    u32 *p;
    s32 n;

    i = 0;
    p = D_8008B1FC;
    while (i < 2) {
        if (*p == 0) {
            n = D_8008B204;
            *p = v;
            D_8008B204 = n + 1;
            return 0;
        }
        i++;
        p++;
    }
    return 1;
}
