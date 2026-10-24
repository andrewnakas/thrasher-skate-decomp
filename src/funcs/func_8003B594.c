#include "common.h"

typedef struct {
    u8 pad0[0x18];
    u8 flag;
    u8 pad19[0x57];
} Rec_8003B594;

extern Rec_8003B594 D_8008234C[];
extern s32 D_8008A6D4;

s32 func_8003B594(s32 a0) {
    s32 old = D_8008A6D4;
    s32 i;

    D_8008A6D4 = a0;

    for (i = 0; i < 2; i++) {
        if (a0) {
            D_8008234C[i].flag = 1;
        } else {
            D_8008234C[i].flag = 0;
        }
    }

    return old;
}
