#include "common.h"

extern u8 D_800A4F04[0x40];

u8 *func_8002AAE4(s32 id, u8 *arg) {
    u8 *e;

    if (id == -1) {
        return 0;
    }
    for (e = *(u8 **) D_800A4F04; e != 0; e = *(u8 **) (e + 0x94)) {
        s32 n = *(u16 *) (e + 0x22);

        if (n != 0) {
            u8 *p = *(u8 **) (e + 0x14);

            while (--n != -1) {
                if (*(u16 *) (p + 2) == id) {
                    return p;
                }
                p += 0x10;
            }
        }
    }
    return 0;
}
