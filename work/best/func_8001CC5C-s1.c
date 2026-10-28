#include "common.h"

extern u16 D_8008AE58;
extern u8 *D_8008AE54;

s32 func_8001CC5C(u32 *obj, u32 arg, u32 *out) {
    u16 key = arg;
    s32 found = 0;
    s32 idx = 0;
    s32 r = 0;
    u16 *tab;
    s32 n;
    s32 flags;

    *out = 0;
    if (!(*obj & 1)) {
        n = D_8008AE58;
        tab = (u16 *) D_8008AE54;
        while (idx < n) {
            if (tab[0] == key) {
                r = *(u32 *) (tab + 2);
                found = 1;
                break;
            }
            idx++;
            tab += 4;
        }
    }
    if (!found) {
        flags = (*obj & 0x8000000) != 0;
        if (*obj & 0x4000000) {
            flags |= 2;
        }
        if (*obj & 1) {
            flags |= 4;
        }
        r = func_80013ECC(arg & 0xFFFF, flags);
        if (r == 0) {
            return 0;
        }
        func_8001CD7C(r, arg & 0xFFFF);
        *out = 1;
        func_8001CDA4(r, obj);
    }
    return r;
}
