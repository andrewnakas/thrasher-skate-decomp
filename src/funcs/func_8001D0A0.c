#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 unk8;
} Ent_8001D0A0;

extern Ent_8001D0A0 *D_8008AE84;
extern s32 D_8008AE88;

s32 func_8001D0A0(u32 i) {
    s32 off;

    if (i >= D_8008AE84->unk8) {
        i = 0;
    }
    off = i * 100 + 8;
    return D_8008AE88 + off;
}
