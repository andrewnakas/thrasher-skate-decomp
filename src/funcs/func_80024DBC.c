#include "common.h"

extern void func_800331FC(u8 *p, s32 v);
extern void func_80032FF4(u8 *a, u8 *b);

void func_80024DBC(u8 *a, u8 *b) {
    func_800331FC(b, 0x3333);
    func_800331FC(a, 0xCCCC);
    func_80032FF4(a, b);
}
