#include "common.h"

void *func_80034C20(s32);
void func_80034BD8(void *);
void func_80019884(void *, s32, s32, s32, s32);
s32 func_80019C38(s32, s32, s32, s32);

s32 func_80019F10(s32 mode, s32 a1, s32 a2, s32 a3, s32 a4) {
    void *buf;
    s32 ret = 1;

    switch (mode) {
    case 1:
        buf = func_80034C20(0x4010);
        func_80019884(buf, a1, a2, a3, a4);
        func_80034BD8(buf);
        return 0;
    case 2:
        if (func_80019C38(a3, a4, a1, a2) != ret) {
            ret = 0;
        } else {
            return 1;
        }
        return ret;
    }
    return 1;
}
