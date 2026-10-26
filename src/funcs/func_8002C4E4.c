/* cflags: -G0 */
#include "common.h"

extern u8 *D_800A4F04;
s32 func_8002C454(u8 *);

s32 func_8002C4E4(u32 *out, s32 key, s32 arg2, s32 flags) {
    u8 *node;
    u8 *rec;
    u8 *p;
    u32 *o;
    s32 count;
    s32 num;
    s32 i;

    node = D_800A4F04;
    count = 0;
    while (node != 0) {
        for (i = 0; i < *(u16 *)(node + 0x1C); i++) {
            rec = node + i * 0x18;
            num = *(u16 *)(rec + 0x52);
            p = *(u8 **)(rec + 0x4C);
            if (num > 0) {
                /* the index is added to the base, not the base to the index: gcc keeps the
                   scaled count as the first operand of the addu the way the original does */
                o = (u32 *)(count * 4 + (u32)out);
                do {
                    if (key == func_8002C454(p)) {
                        if (flags != 0 || (*(u16 *)p & 0x10) == 0) {
                            *o = (u32)p;
                            o++;
                            count++;
                        }
                    }
                    p += p[2];
                } while (--num > 0);
            }
        }
        node = *(u8 **)(node + 0x94);
    }
    return count;
}
