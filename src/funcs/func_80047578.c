#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    u8 pad4[4];
} Rect_80047578;

extern s16 func_80047420(u16);
extern s16 func_80047460(u16);
extern Rect_80047578 D_800828B4[];
extern s32 D_8008A800;

s16 func_80047578(u16 id) {
    s16 x;
    s16 y;
    s32 i;

    x = func_80047420(id);
    y = func_80047460(id);
    for (i = 0; i < D_8008A800; i++) {
        if (x >= D_800828B4[i].x && x < D_800828B4[i].x + 0x80 && y >= D_800828B4[i].y && y < D_800828B4[i].y + 0x100) {
            return y - D_800828B4[i].y;
        }
    }
    return -1;
}
