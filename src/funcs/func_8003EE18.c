#include "common.h"

extern u32 D_8008A788[2];
extern u32 D_8008A790[2];

void func_80034D30(u32);

s32 func_8003EE18(void) {
    s32 i;

    for (i = 1; i >= 0; i--) {
        if (D_8008A790[i] != 0) {
            func_80034D30(D_8008A790[i]);
            D_8008A790[i] = 0;
        }
        if (D_8008A788[i] != 0) {
            func_80034D30(D_8008A788[i]);
            D_8008A788[i] = 0;
        }
    }
    return 1;
}
