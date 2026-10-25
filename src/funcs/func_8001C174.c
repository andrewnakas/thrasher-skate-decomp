#include "common.h"

void func_8001C410(void);
void func_8001CE40(void);
s32 func_80046590(void);
extern s32 D_8008AE9C;
extern s32 D_8008AE70;
extern s32 D_8008AE74;

s32 func_8001C174(void) {
    s32 t;

    func_8001C410();
    func_8001CE40();
    t = func_80046590();
    D_8008AE70 = t;
    D_8008AE74 = D_8008AE9C;
    return 0;
}
