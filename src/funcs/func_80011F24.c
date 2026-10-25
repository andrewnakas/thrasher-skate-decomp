#include "common.h"

extern s32 D_8008ACA0;

void func_80011F24(s32 *a, s32 *b) {
    a[0] = *(s32 *) D_8008ACA0;
    a[1] = *((s32 *) D_8008ACA0 + 1);
    a[2] = *((s32 *) D_8008ACA0 + 2);
    b[0] = *((s32 *) D_8008ACA0 + 3);
    b[1] = *((s32 *) D_8008ACA0 + 4);
    b[2] = *((s32 *) D_8008ACA0 + 5);
}
