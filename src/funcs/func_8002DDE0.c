#include "common.h"

extern u8 *D_8008B060;
extern u8 *D_8008B05C;

u8 *func_8002DDE0(u32 key) {
    u8 *p;

    p = D_8008B060;
    while ((p -= 0xC) >= D_8008B05C) {
        if (*(u32 *) p == key) {
            return p;
        }
    }
    return 0;
}
