#include "common.h"

extern void func_8002DA40(u8 *);
extern s32 func_8002D9BC(u8 *);

s32 func_8002D904(u8 *arg0) {
    s32 flag = 0;
    u8 *n;
    u8 *p;
    s32 i;
    s32 last;

    func_8002DA40(arg0);
    n = *(u8 **) (arg0 + 8);
    while (n != 0) {
        if (func_8002D9BC(n) != 0) {
            flag = 1;
        }
        n = *(u8 **) (n + 0x40);
    }
    i = 3;
    last = -1;
    p = arg0 + 0xC;
    do {
        n = *(u8 **) (p + 0x34);
        if (n != 0) {
            if (func_8002D9BC(n) != 0) {
                flag = 1;
            }
        }
        i--;
        p -= 4;
    } while (i != last);
    return flag;
}
