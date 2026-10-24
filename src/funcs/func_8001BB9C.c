#include "common.h"

extern u8 *D_80089FD0;
extern u8 *D_80089FD4;
extern u8 *D_80089FD8;
extern s32 func_8002BA54(void);
extern u8 *func_80034C20(s32);
extern void *memset(void *, s32, u32);

void func_8001BB9C(void) {
    s32 n;
    u8 *p;

    n = func_8002BA54();
    p = func_80034C20(n * 4);
    D_80089FD0 = p;
    memset(p, 0, n * 4);
    p = func_80034C20(n * 4);
    D_80089FD4 = p;
    memset(p, 0, n * 4);
    p = func_80034C20(n * 0x1C0);
    D_80089FD8 = p;
    memset(p, 0, n * 0x1C0);
}
