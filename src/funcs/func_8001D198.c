#include "common.h"

typedef struct {
    u8 pad0[8];
    u16 unk8;
} Ent_8001D198;

extern Ent_8001D198 *D_8008AE94;
extern s32 D_8008AE98;

s32 func_8001D198(u16 i) {
    s32 off;

    if (i >= D_8008AE94->unk8) {
        return 0;
    }
    off = i * 24 + 8;
    return D_8008AE98 + off;
}
