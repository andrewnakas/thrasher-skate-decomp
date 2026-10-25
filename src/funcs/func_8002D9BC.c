#include "common.h"

/* the s32 immediately below D_800A1C80 in the game's data; the base symbol
   doubles as the anchor so both addresses come out absolute, not %gp_rel */
extern s32 D_800A1C80[4];

extern s32 func_8002F4A0(s32 *, s32 *);
extern s32 *func_8002DAC4(s32 *);
extern s32 func_8002D0B0(s32 *);

s32 func_8002D9BC(s32 *p) {
    s32 *q;

    if (p[0] & 0x2400000) {
        return 0;
    }
    if (!func_8002F4A0(D_800A1C80, p)) {
        return 0;
    }
    q = func_8002DAC4(p);
    if (!q) {
        return 0;
    }
    if (!func_8002D0B0(q)) {
        return 0;
    }
    D_800A1C80[-1] = (s32) p;
    return 1;
}
