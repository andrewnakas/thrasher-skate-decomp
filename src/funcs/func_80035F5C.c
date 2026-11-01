#include "common.h"

extern s32 D_8008A574;

s32 func_80037070(s32, u8 *, u32, void (*)(), void *, s32 *, s32 *);
s32 func_80037968(s32 arg0, s32 arg1);

s32 func_80035F5C(s32 file, u8 *dst, u32 size) {
    s32 got;
    s32 id;
    s32 r;

    if (size == 0) {
        return 1;
    }
    if (D_8008A574 != 0) {
        do {
            if (func_80037070(file, dst, size, NULL, NULL, &got, &id) == 0) {
                return 1;
            }
            r = func_80037968(id, 1);
            if (r == 4) {
                return 0;
            }
        } while (r != 0);
    }
    return 1;
}
