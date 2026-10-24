#include "common.h"

extern u8 D_8008ABF4[];
extern s32 MemCardGetDirentry(s32, void *, void *, s32 *, s32, s32);
extern void func_800382F0(u8 *, void *);
extern s32 func_8003834C(void);

s32 func_80057308(void) {
    u8 buf[0xC8];
    u8 dirent[0x78];
    s32 count;

    func_800382F0(D_8008ABF4, buf);
    if (MemCardGetDirentry(0, buf, dirent, &count, 0, 1) != 0) {
        return 1;
    }
    if (count != 0) {
        return 0;
    }
    return (u32) func_8003834C() < 0x774;
}
