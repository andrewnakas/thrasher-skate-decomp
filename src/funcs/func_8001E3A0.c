#include "common.h"

void func_8001446C(s32, s32, s32 *, s32 *, s32);
s32 func_80032C28(s32, s32);
void func_800333C8(s32 *, s16);
void func_80033428(s32 *, s16);
void func_80033480(s32 *, s16);

/* Applies arg0's rotation and translation to the point at arg2, or hands the
   work to func_8001446C when the object carries a tag other than 0xFF; a null
   object copies the point through. */
void func_8001E3A0(u8 *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    if (arg0 != 0) {
        if ((arg1 & 0xFFFF) != 0xFF) {
            func_8001446C((s32) arg0, arg1 & 0xFFFF, arg2, arg3, 1);
        } else {
            arg3[0] = arg2[0];
            arg3[1] = arg2[1];
            arg3[2] = arg2[2];
            if (*(u32 *) (arg0 + 4) & 8) {
                arg3[0] = func_80032C28(arg3[0], *(s32 *) (arg0 + 0x20));
                arg3[1] = func_80032C28(arg3[1], *(s32 *) (arg0 + 0x24));
                arg3[2] = func_80032C28(arg3[2], *(s32 *) (arg0 + 0x28));
            }
            func_800333C8(arg3, *(s16 *) (arg0 + 0x1A));
            func_80033428(arg3, (s16) - *(u16 *) (arg0 + 0x1C));
            func_80033480(arg3, *(s16 *) (arg0 + 0x1E));
            arg3[0] += *(s32 *) (arg0 + 0xC);
            arg3[1] += *(s32 *) (arg0 + 0x10);
            arg3[2] += *(s32 *) (arg0 + 0x14);
        }
    } else {
        arg3[0] = arg2[0];
        arg3[1] = arg2[1];
        arg3[2] = arg2[2];
    }
}
