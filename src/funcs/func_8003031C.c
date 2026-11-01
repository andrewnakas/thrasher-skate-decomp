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
    s32 off;
    s32 *cnt;

    i = 0;
    {
        u8 *base;
        u8 *q = func_8002E8C0(*(u16 *) a0);

        base = D_8006F890;
        cnt = (s32 *) (base + *q * 8);
    }
    n = cnt[0];
    m = cnt[1];
    func_800337C4(m1);
    func_8003384C(m1, *(s16 *) (a0 + 0x4));
    func_80033A18(m1, *(s16 *) (a0 + 0x6));
    func_80033BE4(m1, *(s16 *) (a0 + 0x8));
    func_80033818(m1);
    func_800337C4(m2);
    func_8003384C(m2, *(s16 *) (a1 + 0x0));
    func_80033A18(m2, *(s16 *) (a1 + 0x2));
    func_80033BE4(m2, *(s16 *) (a1 + 0x4));
    for (; i < n; i++) {
        p = a0 + i * 8;
        d[0] = (*(s16 *) (p + 0x44) - *(s16 *) (a0 + 0xA)) << 16;
        d[1] = (*(s16 *) (p + 0x46) - *(s16 *) (a0 + 0xC)) << 16;
        d[2] = (*(s16 *) (p + 0x48) - *(s16 *) (a0 + 0xE)) << 16;
        func_80033714(m1, d, o);
        func_80033714(m2, o, d);
        *(u16 *) (p + 0x44) = *(u16 *) (a0 + 0xA) + (u16) ((d[0] + 0x8000) >> 16);
        *(u16 *) (p + 0x46) = *(u16 *) (a0 + 0xC) + (u16) ((d[1] + 0x8000) >> 16);
        *(u16 *) (p + 0x48) = *(u16 *) (a0 + 0xE) + (u16) ((d[2] + 0x8000) >> 16);
    }
    for (i = 0; i < m; i++) {
        off = i * 0x2C + 0x84;
        func_8002DAE8(a0 + off);
    }
    func_8002F52C(a0);
    i = *(s16 *) (a0 + 0x28);
    if (i != 0) {
        func_8002FEE0(a0, *(u32 *) (a0 + 0x24));
    }
}
