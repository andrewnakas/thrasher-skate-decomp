#include "common.h"

extern void func_80033E14(u8 *, u8 *);
extern void func_8001483C(u8 *, s16 *, s16 *, u8 *, u8 *);

void func_800147E0(u8 *a0, u8 *a1) {
    s16 v[3];
    u8 buf[0x30];

    func_80033E14(a1, buf);
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    func_8001483C(a0, v, (s16 *)(buf + 0xC), buf, buf);
}
