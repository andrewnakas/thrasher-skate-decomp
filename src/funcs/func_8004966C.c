#include "common.h"

extern s32 D_8008A804;
#define D_8008A800_s32 (*(&D_8008A804 - 1))
extern char D_8008A8F8[];

s32 func_80049A14(u8, u16, u16, u16 *, u16 *);
void func_8004995C(u8, u16, u16, u16, u16, s32);

s32 func_8004966C(u16 *slot, u16 *x, u16 *y, s32 w, s32 h) {
    u16 px;
    u16 py;
    s32 i;
    u16 tw;
    u16 th;
    s32 hh;

    w = (w + 7) & -8;
    hh = (h + 7) & -8;
    w = (u16) w >> 3;
    px = 0xFF;
    py = 0xFF;
    hh = (u16) hh >> 3;
    if (*slot == 0xFF) {
        if (*x == 0xFF || *y == 0xFF) {
            tw = w;
            for (i = D_8008A800_s32 - 1; i >= 0; i--) {
                if (func_80049A14(i, tw, hh, &px, &py) == 0) {
                    func_8004995C(i, px, py, tw, hh, 1);
                    *slot = i;
                    goto done;
                }
            }
            goto fail;
        } else {
            tw = w;
            px = *x;
            py = *y;
            for (i = D_8008A800_s32 - 1; i >= 0; i--) {
                if (func_80049A14(i, tw, hh, &px, &py) == 0) {
                    func_8004995C(i, px, py, tw, hh, 1);
                    *slot = i;
                    goto done;
                }
            }
            goto fail;
        }
    }
    if (*x == 0xFF || *y == 0xFF) {
        u16 tw2;
        u16 th2;

        tw2 = w;
        th2 = hh;
        if (func_80049A14(*slot, tw2, th2, &px, &py) == 0) {
            func_8004995C(*slot, px, py, tw2, th2, 1);
        } else {
            printf(D_8008A8F8, *slot);
            do {
                return 1;
            } while (0);
        }
    } else {
        px = *x >> 3;
        py = *y >> 3;
        func_8004995C(*slot, px, py, w, hh, 1);
        return 0;
    }
done:
    *x = px * 8;
    *y = py * 8;
    return 0;
fail:
    return 1;
}
