/* cflags: -mno-split-addresses */
#include "common.h"

extern u8 D_800A964C[];
extern void *D_8008B390[3];
extern void func_80042300(void);
extern void *func_80034C20(s32);

s32 func_8003F908(void) {
    u8 *p;

    func_80042300();
    memset(D_800A964C, 0, 0x100);
    p = func_80034C20(0xC00);
    D_8008B390[0] = p;
    memset(p, 0, 0xC00);
    return 0;
}
