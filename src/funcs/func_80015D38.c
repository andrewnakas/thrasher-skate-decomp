/* cflags: -O1 */
#include "common.h"

extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;

s32 func_80015D38(s32 arg0) {
    s32 count;
    u8 *p;
    u8 *end;

    count = 0;
    end = D_8008AD3C;
    p = D_8008AD38;
    p -= 0x10;
    for (;;) {
        count++;
        if (*p != 0 && *(s32 *)(p + 4) == arg0) {
            return count;
        }
        if (end < p) {
            p -= 0x10;
        } else {
            return 0;
        }
    }
}
