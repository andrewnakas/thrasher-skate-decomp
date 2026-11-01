#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 unk6;
} Zone_8004734C;

extern s16 func_80047420(u16);
extern s16 func_80047460(u16);
extern Zone_8004734C D_800828B4[];
extern s32 D_8008A800;

u8 func_8004734C(u16 id) {
    s16 x = func_80047420(id);
    s16 y = func_80047460(id);
    u8 i;

    for (i = 0; i < D_8008A800; i++) {
        Zone_8004734C *z = &D_800828B4[i];
        if (x >= z->x && x < z->x + 0x80 && y >= z->y && y < z->y + 0x100) {
            return i;
        }
    }
    return 0xFF;
}
