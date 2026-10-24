#include "common.h"

typedef struct {
    u8 pad0[0x18];
    u8 unk18;
    u8 pad19[0x57];
} Ent_8003B594;

extern s32 D_8008A6D4;
extern Ent_8003B594 D_8008234C[];

s32 func_8003B594(s32 v) {
    s32 old;
    s32 i;

    old = D_8008A6D4;
    D_8008A6D4 = v;
    for (i = 0; i < 2; i++) {
        if (v != 0) {
            D_8008234C[i].unk18 = 1;
        } else {
            D_8008234C[i].unk18 = 0;
        }
    }
    return old;
}
