#include "common.h"

extern void func_80041240(void *, s32, void *);

void func_80013FD0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;

    *(s32 *)(arg0 + 4) |= 0x80;
    for (i = 0; i < *(u16 *)(arg0 + 0x178); i++) {
        if (*(s32 *)(arg0 + i * 0x10 + 0x17C) != arg2) {
            continue;
        }
        *(s32 *)(arg0 + i * 0x10 + 0x188) = arg1;
        if (*(s32 *)arg0 != 1) {
            return;
        }
        func_80041240(*(void **)(arg0 + i * 0x10 + 0x184), arg1,
                      (u8 *)(*(s32 *)(arg0 + 0x38) + 0x134));
        return;
    }
}
