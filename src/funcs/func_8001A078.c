#include "common.h"

s32 func_8001C1B0(void);
void func_8001D7A8(void);
s32 func_800276EC(void);

s32 func_8001A078(void) {
    if (func_8001C1B0() != 0) {
        return 1;
    }
    func_8001D7A8();
    func_800276EC();
    return 0;
}
