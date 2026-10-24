#include "common.h"

s32 func_80058FA4(s32);

char *func_800165DC(char *arg0) {
    char *p = arg0;

    if (*p != 0) {
        do {
            if ((u8)(*p - 'a') < 26) {
                *p = func_80058FA4(*p);
            }
            p++;
        } while (*p != 0);
    }
    return arg0;
}
