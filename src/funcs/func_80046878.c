#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    u8 pad4[4];
} Rect46878;

extern Rect46878 D_800828B4[];
extern s32 D_8008A800;

s32 func_80046878(u16 x, u16 y) {
    s32 i;

    for (i = 0; i < D_8008A800; i++) {
        if (D_800828B4[i].x <= x && x < D_800828B4[i].x + 0x80 &&
            D_800828B4[i].y <= y && y < D_800828B4[i].y + 0x100) {
            return (i << 16) + ((x & 0x7F) << 9) + (y & 0xFF);
        }
    }
    return -1;
}
