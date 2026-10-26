#include "common.h"

extern s32 D_80089F68;
extern s32 D_80089F6C;
extern s32 D_80089F70;
extern s32 D_8008AD4C;

void func_800162FC(void);
s32 func_80015760(void);

s32 func_800159D8(u32 arg0) {
    u32 size;
    u32 len;
    u32 rem;
    u8 *p;

    if (D_80089F68 == 0) {
        return 0;
    }
    size = arg0;
    if (size == 0) {
        return 0;
    }
    func_800162FC();
    p = (u8 *)D_8008AD4C;
    if (p == (u8 *)-1) {
        return 0;
    }
    len = size;
    if (size < 0x10) {
        size = 0x10;
        len = size;
    }
    rem = len & 3;
    if (rem != 0) {
        rem = rem - 4;
        len = len - rem;
    }
    D_80089F70 = D_80089F70 + 1;
    D_80089F6C = D_80089F6C + len;
loop:
    if (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == NULL) {
            return 0;
        }
        goto loop;
    }
    return func_80015760();
}
