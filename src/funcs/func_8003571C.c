#include "common.h"

/* 6-byte row in the table addressed through D_8008A6DC's scale. */
typedef struct {
    u16 f0;             /* 0x0 */
    u16 f2;             /* 0x2 */
    u16 f4;             /* 0x4 */
} T_8003571C_row;

extern u32 D_8008A6DC[];

s32 func_8003571C(u8 *arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4) {
    T_8003571C_row *row;
    u32 off;

    off = arg1 * 6 + 0x20;
    row = (T_8003571C_row *) (arg0 + off);
    row->f2 = arg2;
    row->f0 = arg3;
    if (arg4 & 1) {
        row->f4 = (arg2 & 0xFFFF) / ((arg3 & 0xFFFF) / (s32) D_8008A6DC[0]);
    } else {
        row->f4 = 0;
    }
    return 0;
}
