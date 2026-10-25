#include "common.h"

void func_8002B77C(u8 *, u16 *);

void func_8002B818(u8 *p, u16 *src) {
    u16 t[3];

    t[0] = src[0] + *(u16 *) (p + 4);
    t[1] = src[1] + *(u16 *) (p + 6);
    t[2] = src[2] + *(u16 *) (p + 8);
    func_8002B77C(p, t);
}
