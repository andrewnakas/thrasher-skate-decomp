#include "common.h"

extern s32 D_8008A658[];
extern s32 D_8008A65C[];
extern s32 D_8008A660[];
void func_8001651C(void *, void *);
void func_8001655C(void *, void *);

void *func_80037B4C(s32 a0, void *b) {
    func_8001651C(b, D_8008A658);
    func_8001655C(b, D_8008A65C);
    func_8001655C(b, D_8008A660);
    func_8001655C(b, (void *) a0);
    return b;
}
