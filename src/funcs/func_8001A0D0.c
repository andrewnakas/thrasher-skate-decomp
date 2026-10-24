#include "common.h"

extern void (*D_8008A078)(s32);

void func_8001DC98(void);

s32 func_8001A0D0(s32 arg0) {
    if (D_8008A078 != 0 && arg0 != 0) {
        D_8008A078(arg0);
    }
    func_8001DC98();
    return 0;
}
