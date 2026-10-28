#include "common.h"

extern u8 *D_8008B05C;
extern u8 *D_8008B060;

u8 *func_8002DDE0(u32 key) {
    u8 *p = D_8008B060 - 0xC;
    u8 *base = D_8008B05C;
    u8 *r = 0;

    goto test;
body:
    if (*(u32 *) p == key) {
        r = p;
        goto done;
    }
    p -= 0xC;
test:
    if (p >= base) {
        goto body;
    }
done:
    return r;
}
