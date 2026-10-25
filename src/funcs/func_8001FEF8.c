#include "common.h"

void func_80032FF4(u8 *, u8 *);
void func_8001EB4C(u8 *);
void func_8001DB74(u8 *);

void func_8001FEF8(u8 *p) {
    func_80032FF4(p + 0x10, p + 0x44);
    func_8001EB4C(p);
    if (*(s32 *) (p + 0x1C) != 0) {
        if (*(s32 *) (*(s32 *) (p + 0x1C) + 0x10) < *(s32 *) (p + 0x14)) {
            func_8001DB74(p);
        }
    }
}
