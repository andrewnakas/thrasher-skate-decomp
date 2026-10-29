/* cflags: -fno-strength-reduce */
#include "common.h"

extern u8 D_8006F890[];

u8 *func_8002E8C0(s32);
void func_800337C4(void *);
void func_8003384C(void *, s32);
void func_80033A18(void *, s32);
void func_80033BE4(void *, s32);
void func_80033818(void *);
void func_80033714(void *, void *, void *);
void func_8002DAE8(void *);
void func_8002F52C(void *);
void func_8002FEE0(void *, s32);

void func_8003031C(u8 *a0, u8 *a1) {
    u8 m1[0x30];
    u8 m2[0x30];
    s32 d[3];
    s32 o[3];
    u8 *p;
    s32 n;
    s32 m;
    s32 i;
    s32 k;

    k = *(u8 *) func_8002E8C0(*(u16 *) a0);
    n = *(s32 *) (D_8006F890 + k * 8);
    m = *(s32 *) (D_8006F890 + k * 8 + 4);
    func_800337C4(m1);
    func_8003384C(m1, *(s16 *) (a0 + 0x4));
    func_80033A18(m1, *(s16 *) (a0 + 0x6));
    func_80033BE4(m1, *(s16 *) (a0 + 0x8));
    func_80033818(m1);
    func_800337C4(m2);
    func_8003384C(m2, *(s16 *) (a1 + 0x0));
    func_80033A18(m2, *(s16 *) (a1 + 0x2));
    func_80033BE4(m2, *(s16 *) (a1 + 0x4));
    p = a0;
    for (i = 0; i < n; i++, p += 8) {
        d[0] = (*(s16 *) (p + 0x44) - *(s16 *) (a0 + 0xA)) << 16;
        d[1] = (*(s16 *) (p + 0x46) - *(s16 *) (a0 + 0xC)) << 16;
        d[2] = (*(s16 *) (p + 0x48) - *(s16 *) (a0 + 0xE)) << 16;
        func_80033714(m1, d, o);
        func_80033714(m2, o, d);
        *(u16 *) (p + 0x44) = *(u16 *) (a0 + 0xA) + (u16) ((d[0] + 0x8000) >> 16);
        *(u16 *) (p + 0x46) = *(u16 *) (a0 + 0xC) + (u16) ((d[1] + 0x8000) >> 16);
        *(u16 *) (p + 0x48) = *(u16 *) (a0 + 0xE) + (u16) ((d[2] + 0x8000) >> 16);
    }
    p = a0 + 0x84;
    for (i = 0; i < m; i++, p += 0x2C) {
        func_8002DAE8(p);
    }
    func_8002F52C(a0);
    if (*(s16 *) (a0 + 0x28) != 0) {
        func_8002FEE0(a0, *(u32 *) (a0 + 0x24));
    }
}
