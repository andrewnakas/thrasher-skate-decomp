#include "common.h"

extern s32 func_80032C28(s32, s32);

void func_80026EC8(s32 m[3][3], s32 n[3][3], s32 p[3][3]) {
    s32 i;
    s32 j;
    s32 k;

    for (i = 2; i >= 0; i--) {
        for (j = 2; j >= 0; j--) {
            m[j][i] = 0;
            for (k = 2; k >= 0; k--) {
                m[j][i] += func_80032C28(n[k][i], p[j][k]);
            }
        }
    }
}
