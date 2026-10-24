#include "common.h"

typedef struct {
    u8 pad[0x3000];
} Buf_800471E8;

extern Buf_800471E8 D_800AB794;
extern u16 D_8008B3B4;
extern u16 D_8008B3BE;
void func_8004669C(u16, s32, s32, s32, s32, s32, s32);
void func_80049530(void);

void func_800471E8(void) {
    s32 i;

    memset(&D_800AB794, 0, 0x3000);
    for (i = 0; i < 0x300; i++) {
        func_8004669C(i, 8, 0, 0, 0, 4, 4);
    }
    D_8008B3B4 = 0;
    D_8008B3BE = 0;
    func_80049530();
}
