#include "common.h"

typedef struct {
    s16 a, b, c;
} Trip;

extern s32 D_8008A920[2];
extern s32 D_8008B3E8[2];
extern s32 D_80082918[][3];
extern s32 D_800828F4[][3];

s32 func_80049BF4(s32 *a0, s32 *a1, s16 a2, s16 a3, s16 a4);

void func_8004A094(void) {
    u32 i;

    for (i = 0; i < 3; i++) {
        D_8008B3E8[i] = func_80049BF4(D_800828F4[i], D_80082918[i], ((Trip *) D_8008A920)[i].a,
                                      ((Trip *) D_8008A920)[i].b, ((Trip *) D_8008A920)[i].c);
    }
}
