/* cflags: -mno-split-addresses */
#include "common.h"

extern u8 D_8008A6F0[0x10];
void func_80032A9C(u16 v);

void func_80032AF4(void) {
    u16 v = *(u16 *) D_8008A6F0;

    func_80032A9C(v);
}
