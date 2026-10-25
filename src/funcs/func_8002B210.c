#include "common.h"

extern u8 D_800A1C90[];
extern void func_8002B360(u8 *a0, s32 a1);

void func_8002B210(u8 *self) {
    u8 *s2 = D_800A1C90 + *(u16 *) (self + 0x2A) * 36;

    if (*(s16 *) (s2 + 2) != 0) {
        s32 n = 7;
        s32 end = -1;
        u8 *p = s2 + 0x1C;

        for (; n != end; n--) {
            if (*(s32 *) (p + 4) != 0) {
                func_8002B360(self, *(s32 *) (p + 4));
            }
            p -= 4;
        }
    }
    *(u16 *) s2 = 0;
}
