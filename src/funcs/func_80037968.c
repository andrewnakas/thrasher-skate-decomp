#include "common.h"

void func_8003BA14(void);
void func_80059D88(s32);
void VSync(s32);

s32 func_80037968(volatile s32 *arg0, s32 arg1) {
    if (arg1 != 0) {
        if (arg1 == 1) {
            if (*arg0 == 2 || *arg0 == arg1) {
            again:
                func_8003BA14();
                func_80059D88(0);
                VSync(0);
                if (*arg0 == 2) {
                    goto again;
                }
                if (*arg0 == 1) {
                    goto again;
                }
            }
        }
    }
    return *arg0;
}
