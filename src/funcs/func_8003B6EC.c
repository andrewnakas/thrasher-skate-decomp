#include "common.h"

extern s32 D_8008B228;
extern s32 D_8008A6D8;
extern s32 D_8008B23C;
extern s32 D_8008B234;
extern void func_8003B60C(void);

void func_8003B6EC(s32 a0, s32 a1) {
    s32 x;
    s32 y;

    if (D_8008B228 == 0) {
        x = a0 + D_8008A6D8;
        y = x + 0x190;
        if (y >= 0x7D00) {
            y = 0x7D00;
            x = 0x7B70;
        }
    } else {
        y = 0x7FFE;
        x = 0x5400 - D_8008A6D8;
    }

    D_8008B23C = x;
    D_8008B234 = y;
    func_8003B60C();
}
