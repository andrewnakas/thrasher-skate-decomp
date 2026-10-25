#include "common.h"

extern s32 D_8008A168;
extern s32 D_80092824[];

s32 func_8001D1D4(void);
s32 func_8001D198(u16);

void func_8001BFA8(void) {
    s32 i;

    D_8008A168 = func_8001D1D4();
    for (i = 0; i < D_8008A168; i++) {
        D_80092824[i] = func_8001D198(i) + 8;
    }
}
