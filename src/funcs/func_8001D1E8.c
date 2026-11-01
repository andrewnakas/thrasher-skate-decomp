#include "common.h"

typedef struct {
    s32 a;
    s32 b;
} Pair_8001D1E8;

extern s32 D_8006EFB8[];
extern s32 D_8006EF54[];
extern s32 D_8006EE90[];
extern Pair_8001D1E8 D_8006F254[];
extern u8 D_8006EF88[];
extern u8 D_8006EE94[];
extern s32 D_8008AE20[2];
extern s32 D_8008AE28[2];
extern s32 D_8008AE30[2];

extern void func_8001D304(s32 *, s32 *);
extern s32 func_8001D340(s32, s32, u16, s32 *);

s32 *func_8001D1E8(s32 idx, s32 type, s32 arg) {
    s32 *r;
    s32 ok;

    switch ((u32) type) {
    case 0:
        func_8001D304(&D_8006EFB8[idx], D_8008AE20);
        ok = func_8001D340(D_8006F254[idx].a, D_8006F254[idx].b, arg, D_8008AE20);
        r = D_8008AE20;
        break;
    case 1:
        func_8001D304(&D_8006EF54[idx], D_8008AE28);
        do {
            ok = func_8001D340((s32) D_8006EF88, 0xC, arg, D_8008AE28);
            r = D_8008AE28;
        } while (0);
        break;
    case 2:
        func_8001D304(&D_8006EE90[idx], D_8008AE30);
        do {
            ok = func_8001D340((s32) D_8006EE94, 0x30, arg, D_8008AE30);
            r = D_8008AE30;
        } while (0);
        break;
    default:
        return 0;
    }
    if (ok == 0) {
        r = 0;
    }
    return r;
}
