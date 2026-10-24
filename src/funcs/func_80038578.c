#include "common.h"

extern s32 D_8008A618;
extern u8 D_8008B188[4];
extern void MemCardStart(void);
extern void MemCardCallback(void *);
extern void MemCardSync(s32, s32, u8 *);
extern void func_80037B0C(void);

void func_80038578(void) {
    MemCardStart();
    MemCardCallback(func_80037B0C);
    MemCardSync(0, 0, D_8008B188);
    D_8008A618 = 1;
}
