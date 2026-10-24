#include "common.h"

extern u8 D_8008A61C[4];
extern void func_8001651C(u8 *, u8 *);

void func_800385E8(u8 *arg) {
    func_8001651C(D_8008A61C, arg);
}
