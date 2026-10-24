#include "common.h"

extern s32 D_8008A79C;
extern s32 func_8003F9A4(s32);
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern void *func_80034CF0(s32);
extern void func_80036BF4(s32, void *);
extern s32 func_8003FAEC(void *, u16, s32);
extern void func_80034D30(void *);

s32 func_8003FA30(s32 a0, s32 a1) {
    s32 r;
    u8 *p;

    if (!(a1 & 4)) {
        r = func_8003F9A4(a0);
        if (r != 0) {
            return r;
        }
    }
    if (func_80036A78(D_8008A79C, a0, 0) != 0) {
        return 0;
    }
    p = func_80034CF0(func_80036B18(D_8008A79C));
    func_80036BF4(D_8008A79C, p);
    r = func_8003FAEC(p, (u16) a0, a1);
    func_80034D30(p);
    return r;
}
