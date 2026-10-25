#include "common.h"

extern u8 D_800A4F04[0x40];

u8 *func_8002B708(u32 key, s32 n) {
    u8 *p = *(u8 **) D_800A4F04;
    u8 *e;

    while (p != 0) {
        e = *(u8 **) (p + 8);
        while (e != 0) {
            if (key == (*(u16 *) (e + 2) & 0x1F)) {
                if (--n == -1) {
                    return e;
                }
            }
            e = *(u8 **) (e + 0x40);
        }
        p = *(u8 **) (p + 0x94);
    }
    return 0;
}
