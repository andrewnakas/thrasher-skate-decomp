#include "common.h"

extern s32 D_8008A614;
extern s32 D_8008A618;
extern s32 D_8008B188;
void func_800385B8(void);
void MemCardCallback(s32);
void MemCardEnd(void);
void MemCardSync(s32, s32, s32 *);

void func_80037D50(void) {
    if (D_8008A614 != 0) {
        if (D_8008A618 == 1) {
            func_800385B8();
        }
        MemCardCallback(0);
        MemCardEnd();
        MemCardSync(0, 0, &D_8008B188);
        D_8008A614 = 0;
    }
}
