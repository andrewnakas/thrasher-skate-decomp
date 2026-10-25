/* cflags: -fno-schedule-insns */
#include "common.h"

extern s32 D_8008B1A8;
extern s32 GetVideoMode(void);

void func_8003A4A0(s32 a0, s32 a1, s32 a2, s32 a3, s32 f5, s32 f6) {
    u32 *e;
    u32 *p;
    
    p = (u32 *) 0x1F800000;
    if (D_8008B1A8 != 0) {
        D_8008B1A8 = 0;
        p[0] = 0;
        p[1] = GetVideoMode();
    }
    e = p + 2 + p[0] * 6;
    e[0] = a0;
    e[1] = a1;
    e[2] = a2;
    e[3] = a3 - 1;
    if (f5 == 0x10) {
        e[4] = 0;
    } else {
        e[4] = 1;
    }
    e[5] = f6;
    p[0] = p[0] + 1;
}
