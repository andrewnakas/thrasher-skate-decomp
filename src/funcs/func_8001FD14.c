#include "common.h"

void func_8001EB4C(u8 *);

void func_8001FD14(u8 *p) {
    p[0x38] -= 4;
    p[0x39] -= 4;
    p[0x3A] -= 4;
    func_8001EB4C(p);
}
