/* cflags: -fno-strength-reduce */
#include "common.h"

typedef struct {
    u32 f0;             /* 0x0 */
    u8 pad4[0x6];
    u16 fA;             /* 0xA */
    u16 fC;             /* 0xC */
    u16 fE;             /* 0xE */
    u8 pad10[0xC];
    s32 f1C;            /* 0x1C */
    u8 pad20[0xA];
    u16 f2A;            /* 0x2A */
    u8 pad2C[0x10];
    s32 f3C;            /* 0x3C */
} T_8002B8CC;

typedef struct {
    s32 f0;             /* 0x0 */
    s32 f4;             /* 0x4 */
    s32 f8;             /* 0x8 */
} T_8002B8CC_arg1;

/* 36-byte rows; the loop walks the last eight words of a row backwards. */
extern u8 D_800A1C90[];
s32 func_80012214(s32, s32 *);
s32 func_8002B194(T_8002B8CC *);
s32 func_8002B360(T_8002B8CC *, s32);
s32 func_8002B3FC(T_8002B8CC *);
s32 func_8002B5DC(T_8002B8CC *, s32);
s32 func_8002B674(T_8002B8CC *, s32);
s32 func_8003012C(T_8002B8CC *, T_8002B8CC_arg1 *);

void func_8002B8CC(T_8002B8CC *arg0, T_8002B8CC_arg1 *arg1) {
    s32 vec[3];
    u8 *row;
    s32 *p;
    s32 v;
    s32 i;

    arg0->fA = (u16) (arg0->fA + ((s32) (arg1->f0 + 0x8000) >> 16));
    arg0->fC = (u16) (arg0->fC + ((s32) (arg1->f4 + 0x8000) >> 16));
    arg0->fE = (u16) (arg0->fE + ((s32) (arg1->f8 + 0x8000) >> 16));
    if (arg0->f1C != 0) {
        vec[0] = (s32) ((s16) arg0->fA << 16);
        vec[1] = (s32) ((s16) arg0->fC << 16);
        vec[2] = (s32) ((s16) arg0->fE << 16);
        func_80012214(arg0->f1C, vec);
    }
    if ((arg0->f0 & 0xC00000) != 0xC00000) {
        func_8003012C(arg0, arg1);
        if (arg0->f2A == 0xFF) {
            arg0->f2A = func_8002B194(arg0);
            func_8002B3FC(arg0);
        }
        if (func_8002B5DC(arg0, arg0->f3C) == 0) {
            row = D_800A1C90 + arg0->f2A * 0x24;
            p = (s32 *) (row + 0x1C);
            for (i = 7; i != -1; i--) {
                v = p[1];
                if ((v != 0) && (func_8002B674(arg0, v) == 0)) {
                    func_8002B360(arg0, p[1]);
                }
                p--;
            }
            func_8002B3FC(arg0);
        }
    }
}
