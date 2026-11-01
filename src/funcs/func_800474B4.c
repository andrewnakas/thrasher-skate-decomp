#include "common.h"

typedef struct {
    s16 x0;
    s16 y0;
    u16 w;
    u16 h;
} Tile_800474B4;

extern Tile_800474B4 D_800828B4[];
extern s32 D_8008A800;
s16 func_80047420(u16);
s16 func_80047460(u16);

s16 func_800474B4(u16 id) {
    s16 a;
    s16 b;
    s32 i;

    a = func_80047420(id);
    b = func_80047460(id);
    for (i = 0; i < D_8008A800; i++) {
        if (a >= D_800828B4[i].x0 && a < D_800828B4[i].x0 + 0x80 && b >= D_800828B4[i].y0
            && b < D_800828B4[i].y0 + 0x100) {
            return (a - D_800828B4[i].x0) * 2;
        }
    }
    return -1;
}
