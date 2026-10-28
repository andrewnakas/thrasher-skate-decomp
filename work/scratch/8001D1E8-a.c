#include "common.h"

typedef struct {
    u32 a;
    u32 b;
} Pair;

extern u8 D_8006EFB8[];
extern u8 D_8006EF54[];
extern u8 D_8006EF88[];
extern u8 D_8006EE90[];
extern u8 D_8006EE94[];
extern Pair D_8006F254[];
extern u8 D_8008AE20[8];
extern u8 D_8008AE28[8];
extern u8 D_8008AE30[8];

void func_8001D304(u8 *, u8 *);
s32 func_8001D340(u32, u32, u32, u8 *);

u8 *func_8001D1E8(s32 idx, s32 kind, u16 arg) {
    u8 *r;

    switch (kind) {
    case 0:
        func_8001D304(D_8006EFB8 + 4 * idx, D_8008AE20);
        r = D_8008AE20;
        if (func_8001D340(D_8006F254[idx].a, D_8006F254[idx].b, arg, D_8008AE20) == 0) {
            r = 0;
        }
        return r;
    case 1:
        func_8001D304(D_8006EF54 + 4 * idx, D_8008AE28);
        r = D_8008AE28;
        if (func_8001D340((u32) D_8006EF88, 0xC, arg, D_8008AE28) == 0) {
            r = 0;
        }
        return r;
    case 2:
        func_8001D304(D_8006EE90 + 4 * idx, D_8008AE30);
        r = D_8008AE30;
        if (func_8001D340((u32) D_8006EE94, 0x30, arg, D_8008AE30) == 0) {
            r = 0;
        }
        return r;
    }
    return 0;
}
