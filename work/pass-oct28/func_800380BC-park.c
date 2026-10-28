#include "common.h"

extern u8 D_8008B150[0x40];
extern u8 D_800A7F2C[0x200];
extern u8 D_800A812C[0x80];
extern s32 D_8008A618;
extern s32 D_8008A63C;
extern s32 D_8008A640;
extern s32 D_8008B188;

extern void func_8001651C(u8 *a0, u8 *a1);
extern s32 func_80037BB8(void);
extern s32 MemCardOpen(s32 a0, u8 *a1, s32 a2);
extern s32 MemCardReadData(u8 *a0, s32 a1, s32 a2);
extern s32 MemCardSync(s32 a0, s32 a1, s32 *a2);
extern void MemCardClose(void);
extern void func_80034D4C(u8 *a0, u8 *a1, s32 a2);
extern s32 func_80037C20(u8 *a0, s32 a1);

s32 func_800380BC(u8 *a0, u8 *a1, s32 a2) {
    s32 s1;
    s32 s3;
    s32 s4;
    s32 s5;
    u8 *s6;
    s32 s0;
    s32 v;

    func_8001651C(D_8008B150, a0);

    if (D_8008A618 == 0) {
        return 1;
    }
    if (func_80037BB8() != 0) {
        return 1;
    }

    D_8008B188 = MemCardOpen(D_8008A63C + D_8008A640, D_8008B150, 1);
    if (D_8008B188 != 0) {
        return 1;
    }

    if (MemCardReadData(D_800A7F2C, 0, 0x200) == 0) {
        MemCardClose();
        return 1;
    }
    MemCardSync(0, 0, &D_8008B188);
    if (D_8008B188 != 0) {
        MemCardClose();
        return 1;
    }

    s6 = a1;
    s3 = 0x200;
    s5 = 0;
    s1 = 1;
    for (;;) {
        s4 = 0;
        for (;;) {
            if (MemCardReadData(D_800A812C, s3, 0x80) == 0) {
                goto fail;
            }
            MemCardSync(0, 0, &D_8008B188);
            if (D_8008B188 != 0) {
                goto fail;
            }
            s3 += 0x80;

            if (s5 == 0) {
                s1 = *(s32 *) D_800A812C;
                if (a2 < s1) {
                    s1 = a2;
                }
                s0 = 0x7B;
            } else {
                s0 = 0x7F;
            }
            if (s1 < 0x7F) {
                s0 = s1;
            }

            func_80034D4C(s6, D_800A812C, s0);
            if ((func_80037C20(D_800A812C, 0x7F) & 0xFF) == D_800A812C[0x7F]) {
                break;
            }
            s4++;
            if (s4 >= 2) {
                goto fail;
            }
            s3 -= 0x80;
        }

        s1 -= s0;
        s6 += s0;
        if (s1 <= 0) {
            break;
        }
        s5++;
    }

    MemCardClose();
    MemCardSync(0, 0, &D_8008B188);
    v = D_8008B188;
    if (v == 0) {
        return 0;
    }
    return 1;

fail:
    MemCardClose();
    return 1;
}
