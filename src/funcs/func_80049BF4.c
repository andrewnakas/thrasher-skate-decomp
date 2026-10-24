#include "common.h"

extern u8 D_8008B3F8;
extern u8 D_800AE994[];

void func_8004A270(u8 *);

u8 *func_80049BF4(s32 *a0, s32 *a1, u16 a2, u16 a3, u16 a4) {
    u16 *r;
    u16 *end;

    if (D_8008B3F8 >= 3) {
        return 0;
    }

    r = (u16 *) D_800AE994;
    end = r + 0x48;
    for (; r < end; r += 0x18) {
        if (r[0] == 0) {
            break;
        }
    }

    r[0] = 1;
    r[1] = a2;
    r[2] = a3;
    r[3] = a4;
    ((s32 *) r)[2] = a0[0];
    ((s32 *) r)[3] = a0[1];
    ((s32 *) r)[4] = a0[2];
    ((s32 *) r)[5] = a1[0];
    ((s32 *) r)[6] = a1[1];
    ((s32 *) r)[7] = a1[2];
    func_8004A270((u8 *) r);
    D_8008B3F8++;
    return (u8 *) r;
}
