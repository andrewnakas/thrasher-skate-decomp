#include "common.h"

typedef struct {
    u16 f0;             /* 0x0 */
} T_8002C77C;

typedef struct {
    s16 x;              /* 0x0 */
    s16 y;              /* 0x2 */
    s16 z;              /* 0x4 */
} V3_8002C77C;

s32 func_8002C77C(T_8002C77C *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    s16 x;
    s16 y;
    s16 z;
    V3_8002C77C *node;

    n = (arg0->f0 & 1) ? 4 : 3;
    x = (s16) arg1;
    y = (s16) arg2;
    z = (s16) arg3;
    while (--n != -1) {
        node = (V3_8002C77C *) (*(u32 *) ((u8 *) arg0 + n * 4 + 0x1C));
        if (node->x == x && node->y == y && node->z == z) {
            return 1;
        }
    }
    return 0;
}
