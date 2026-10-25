#include "common.h"

extern u8 *D_8008AEC4;

void func_8001DB74(u8 *arg0) {
    u8 *rec;
    void (*fp)(void);
    s32 *p;

    *(u16 *)arg0 = 0;
    rec = (u8 *)(*(u16 *)(arg0 + 2) * 0x44 + (s32)D_8008AEC4);
    fp = *(void (**)(void))(rec + 8);
    if (fp != 0) {
        fp();
    }
    p = *(s32 **)(arg0 + 8);
    if (p != 0) {
        *p = 0;
    }
}
