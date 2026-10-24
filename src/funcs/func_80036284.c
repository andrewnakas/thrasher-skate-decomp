#include "common.h"

extern u8 D_8008A5C0[];
extern u8 D_8008A5CC[];
s32 func_8003624C(void);
s32 func_80037AAC(s32);
s32 func_80037ACC(s32, s32, s32);
s32 func_80037AEC(s32);
s32 printf(void *, s32);

s32 func_80036284(s32 a0, s32 a1, s32 a2) {
    s32 fd;

    if (func_8003624C() != 0) {
        printf(D_8008A5CC, a0);
        return 1;
    }
    fd = func_80037AAC(a0);
    if (fd < 0) {
        printf(D_8008A5CC, a0);
        return 1;
    }
    func_80037ACC(fd, a1, a2);
    func_80037AEC(fd);
    printf(D_8008A5C0, a0);
    return 0;
}
