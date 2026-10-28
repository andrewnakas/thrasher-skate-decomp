#include "common.h"

typedef struct {
    s16 x;
    u16 pad;
    s16 y;
} Pnt_80042E9C;

s32 func_80032C54(s32, s32);

s32 func_80042E9C(u8 *a0, s32 a1, s32 a2) {
    s32 k;
    Pnt_80042E9C *rp;
    Pnt_80042E9C *p;

    if (*(u16 *) a0 & 1) {
        k = 3;
    } else {
        k = 2;
    }
    rp = *(Pnt_80042E9C **) (a0 + 0x1C);

    do {
        p = *(Pnt_80042E9C **) (a0 + 0x1C + k * 4);
        if ((p->x - rp->x) * (a2 - rp->y) - (a1 - rp->x) * (p->y - rp->y) < 0) {
            goto fail;
        }
        rp = p;
        k--;
    } while (k != -1);

    if (*(s32 *) (a0 + 8)) {
        return func_80032C54(-(*(s32 *) (a0 + 4) * a1 + *(s32 *) (a0 + 0xC) * a2
            + *(s32 *) (a0 + 0x10)), *(s32 *) (a0 + 8));
    }
    return 0x27100000;

fail:
    return 0x27100001;
}
