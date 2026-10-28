#include "common.h"

extern u8 D_800A4F00[0x40];

extern u8 *func_8001D5B0(s32 a0, s32 a1, s32 a2);
extern void func_8003B8C8(s32 a0, s32 a1, s32 a2);
extern void func_8003C18C(s32 a0, s32 a1);
extern void func_8003B794(void);
extern void func_8003B6EC(s32 a0, s32 a1);
extern void func_8001D974(u8 *p);

void func_80029664(s32 a0, s32 a1, u8 *a2) {
    u8 *s0;
    u8 *dp;
    u8 *sp;
    s32 i;
    s32 b;
    s32 w1;
    s32 w2;
    s32 w3;
    u16 flag;

    if ((*(u32 *) (a2 + 0x18) & 0x400000) == 0) {
        return;
    }

    s0 = func_8001D5B0(a0, 0x4E454742, 1);

    flag = *(u16 *) (s0 + 0xA);
    *(u16 *) D_800A4F00 = flag;
    if (flag & 1) {
        *(u16 *) D_800A4F00 = flag & 0xFFFD;
    }

    sp = s0 + 0xC;
    dp = D_800A4F00 + 0xC;
    for (i = 0; i < 4; i++) {
        *(u16 *) (dp + 0x0) = *(u16 *) (sp + 0x0);
        *(u16 *) (dp + 0x2) = *(u16 *) (sp + 0x2);
        *(u16 *) (dp + 0x18) = 0;
        *(u16 *) (dp + 0x4) = *(u16 *) (sp + 0x4);
        *(u16 *) (dp + 0x1C) = 0;
        *(u16 *) (dp + 0x1A) = *(u16 *) (sp + 0x6);
        sp += 8;
        dp += 6;
    }

    func_8003B8C8(s0[0x4C], s0[0x4D], s0[0x4E]);

    w1 = s0[0x4C] | (s0[0x4D] << 8) | (s0[0x4E] << 16);
    w2 = s0[0x4F] | (s0[0x50] << 8) | (s0[0x51] << 16);
    w3 = s0[0x52] | (s0[0x53] << 8) | (s0[0x54] << 16);

    if (w1 != w2) {
        if ((w2 | w3) != 0) {
            func_8003C18C(w2, w3);
        }
    } else if (w2 != w3) {
        if ((w2 | w3) != 0) {
            func_8003C18C(w2, w3);
        }
    }

    dp = D_800A4F00 + 0x3C;
    sp = s0 + 0x68;
    for (i = 0; i < 4; i++) {
        *(s32 *) dp = *(s32 *) sp;
        sp += 4;
        dp += 4;
    }

    b = *(s32 *) (D_800A4F00 + 0x3C);
    if (b > 0x7FFF) {
        func_8003B794();
    } else {
        func_8003B6EC(0, 0);
    }

    func_8001D974(s0 + 0x58);
}
