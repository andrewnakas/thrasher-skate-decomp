#include "common.h"

void func_80032FF4(u8 *, u8 *);
void func_8001EB4C(u8 *);

void func_8001F984(u8 *p) {
    func_80032FF4(p + 0x10, p + 0x44);
    func_80032FF4(p + 0x44, p + 0x50);
    func_8001EB4C(p);
}
