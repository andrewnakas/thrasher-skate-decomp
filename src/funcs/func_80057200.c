#include "common.h"

extern u8 D_8008ABF0;
void func_80038578(void);
void func_800572AC(void);

void func_80057200(void) {
    func_80038578();
    D_8008ABF0 = 0;
    func_800572AC();
}
