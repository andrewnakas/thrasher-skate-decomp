#include "common.h"

s32 func_8001C3B4(s32);
void func_80042268(s32, s32);
void func_800421D8(s32, s32, s32);

void func_8001AFC8(s32 *arg0, s32 arg1) {
    s32 i;
    s32 flags;

    flags = arg0[0];
    if (flags < 0) {
        for (i = 0; i < 0x16; i++) {
            if (arg0[i + 8] != 0) {
                if (func_8001C3B4(arg0[i + 8]) & 0x80000000) {
                    func_80042268(arg1, (u16)i);
                }
            }
        }
        flags = arg0[0];
    }
    if (flags & 4) {
        func_800421D8(arg1, -3, 2);
    }
    if (arg0[0] & 2) {
        func_800421D8(arg1, -1, 0x200);
    }
    if (arg0[0] & 0x100000) {
        func_800421D8(arg1, -1, 0x1000);
    }
}
