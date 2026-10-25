#include "common.h"

extern u8 *D_8008AD70;
extern u8 *D_8008AD6C;

void func_800194A4(u8 *self) {
    u8 *head = D_8008AD70;

    if (self == head) {
        D_8008AD70 = *(u8 **) (self + 4);
    } else {
        u8 *p = head;

        while (p != 0) {
            u8 *nx = *(u8 **) (p + 4);

            if (nx == self) {
                break;
            }
            p = nx;
        }
        if (p != 0) {
            *(u8 **) (p + 4) = *(u8 **) (self + 4);
        }
    }
    *(u8 **) (self + 4) = D_8008AD6C;
    D_8008AD6C = self;
}
