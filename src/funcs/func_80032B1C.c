#include "common.h"

void func_80033E14(s32 (*a)[3], s32 (*b)[3]);
s32 func_80032C28(s32 a, s32 b);

void func_80032B1C(s32 a[3][3], s32 b[3][3]) {
    s32 t[4][3];
    s32 i;
    s32 j;
    s32 k;

    func_80033E14(a, t);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a[j][i] = 0;
            for (k = 0; k < 3; k++) {
                a[j][i] += func_80032C28(t[k][i], b[j][k]);
            }
        }
    }
}
