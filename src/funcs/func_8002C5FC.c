/* cflags: -G0 */
#include "common.h"
extern u8 *D_800A4F08;
u8 *func_8002C5FC(s32 arg0, s32 arg1, s32 arg2) {
    u8 *node;
    u8 *p;
    s32 n;
    s32 v;
    node = D_800A4F08;
    while (node != 0) {
        n = *(u16 *)(node + 0x52);
        p = *(u8 **)(node + 0x4C);
        while (n > 0) {
            v = 0;
            if (p != 0) {
                v = (*(u16 *)p & 0x7E00) >> 9;
            }
            if (v >= arg0 && arg1 >= v) {
                arg2--;
                if (arg2 == -1) {
                    return p;
                }
            }
            p += p[2];
            n--;
        }
        node = *(u8 **)(node + 0x98);
    }
    return 0;
}
