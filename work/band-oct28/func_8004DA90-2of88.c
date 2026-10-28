#include "common.h"

extern s32 D_8008A960;
extern u32 D_8008B42C;
extern u32 D_8008B430;
extern char D_80010820[];
extern char D_8008A96C[];

extern void func_80011EF4(s32, void *);
extern s32 func_80032DCC(s32);
extern void func_800333C8(void *, s32);

s32 func_8004DA90(s32 a0, u8 *a1, u8 *a2) {
    s16 v[6];
    u32 d;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x18B);
        exit(1);
    }
    func_80011EF4(a0, v);
    d = v[1] * v[1] + v[3] * v[3] + v[5] * v[5];
    if (d < D_8008B430) {
        a1[0] = 0x7F - d * 127 / D_8008B430;
        if (((u32 *) v)[0] != 0 && ((u32 *) v)[2] != 0) {
            if (((u32 *) v)[1] != 0) {
                func_800333C8(v, (s16) -func_80032DCC(((u32 *) v)[1]));
            }
            a2[0] = (((u32 *) v)[0] * 127 / D_8008B42C) >> 16;
        } else {
            a2[0] = 0;
        }
        return 0;
    }
    a1[0] = 0;
    a2[0] = 0;
    return 1;
}
