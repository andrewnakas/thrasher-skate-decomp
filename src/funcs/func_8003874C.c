#include "common.h"

extern s32 D_8008B198;
extern s32 D_8008B19C;
extern s32 func_80034C14(void);
extern void func_8003A060(void);
extern void func_8003A33C(void);

s32 func_8003874C(void) {
    D_8008B198 = func_80034C14();
    func_8003A060();
    func_8003A33C();
    D_8008B19C = 0;
    return 0;
}
