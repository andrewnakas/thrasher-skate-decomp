#include "common.h"

extern u8 *D_8008B05C;
extern u8 *D_8008B060;

u8 *func_8002DDE0(u32 key) {
    u8 *p = D_8008B060 - 0xC;
    u8 *base = D_8008B05C;

    while (p >= base) {
        if (*(u32 *) p == key) {
            return p;
        }
        p -= 0xC;
    }
    return 0;
}
