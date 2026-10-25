#include "common.h"

void func_8001D380(void);
s32 func_8001C0AC(void);

s32 func_80019FCC(void) {
    func_8001D380();
    return func_8001C0AC() != 0;
}
