#include "common.h"

extern s32 D_8008B1FC[2];
extern s32 D_8008B204;

s32 func_8003AA68(s32 a0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8008B1FC[i] == 0) {
            D_8008B1FC[i] = a0;
            D_8008B204++;
            return 0;
        }
    }

    return 1;
}
