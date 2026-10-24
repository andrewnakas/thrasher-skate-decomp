#include "common.h"

extern s32 D_8008A770;
extern void func_8003ECE0(void);

void func_8003C730(void) {
    D_8008A770 = 1;
    func_8003ECE0();
}
