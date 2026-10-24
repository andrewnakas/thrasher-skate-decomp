#include "common.h"

extern s32 D_8008A574;
void func_80052874(void);
void func_800535D4(s32 *);
void func_800535A8(s32);

void func_80036020(void) {
    s32 flag = 0;

    func_80052874();
    while (flag == 0) {
        func_800535D4(&flag);
    }
    func_800535A8(0);
    D_8008A574 = 1;
}
