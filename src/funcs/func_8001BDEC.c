#include "common.h"

extern u8 *D_80089FD4;

u8 *func_80012024(void);
void func_80012004(u8 *, s32);
void func_80012214(u8 *, void *);
s16 func_800122A0(s16);
void func_80012240(u8 *, s16);
void func_800142FC(u8 *);

s32 func_8001BDEC(u16 arg0, u8 *arg1, u16 *arg2) {
    u8 *p;
    s16 v[3];

    p = func_80012024();
    if (p == NULL) {
        return 0;
    }
    func_80012004(p, *(s32 *)(D_80089FD4 + arg0 * 4));
    func_80012214(p, arg1);
    v[0] = arg2[0];
    v[1] = arg2[1];
    v[2] = arg2[2];
    v[1] = func_800122A0(v[1]);
    func_80012240(p, v[1]);
    func_800142FC(p);
    return (s32)p;
}
