#include "common.h"

extern s32 D_8008A614;
extern s32 D_8008B188;
void MemCardInit(s32);

s32 func_80037D10(void) {
    if (D_8008A614 == 0) {
        D_8008B188 = 0;
        MemCardInit(0);
        D_8008A614 = 1;
        return 0;
    }
    return 1;
}
