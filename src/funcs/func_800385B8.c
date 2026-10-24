#include "common.h"

extern u8 D_8008B188[4];
extern s32 D_8008A618;
extern void MemCardStop(void);
extern void MemCardSync(s32, s32, u8 *);

void func_800385B8(void) {
    MemCardStop();
    MemCardSync(0, 0, D_8008B188);
    D_8008A618 = 0;
}
