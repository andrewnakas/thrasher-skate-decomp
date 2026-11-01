#include "common.h"

typedef struct {
    s16 used;
    u8 pad[0x22];
} Rec24;

extern Rec24 D_800A1C90[10];

void *memset(void *, s32, u32);

s32 func_8002B194(void) {
    s32 i;

    for (i = 9; i != -1; i--) {
        if (D_800A1C90[i].used == 0) {
            memset(&D_800A1C90[i], 0, sizeof(Rec24));
            D_800A1C90[i].used = 1;
            return (u16) i;
        }
    }
    return 0;
}
