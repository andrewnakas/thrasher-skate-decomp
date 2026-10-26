#include "common.h"

extern void func_80033804(s32);
extern void func_80026DAC(u8 *, u8 *, s32);
extern void func_80026DEC(void *, void *, void *);
extern void func_800330A4(void *);

void func_8002635C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_80033804(arg5);
    func_80026DAC((u8 *) (arg1 * 140 + (u32) arg0) + 0x48, (u8 *) (arg2 * 140 + (u32) arg0) + 0x48, arg5);
    func_80026DAC((u8 *) (arg3 * 140 + (u32) arg0) + 0x48, (u8 *) (arg4 * 140 + (u32) arg0) + 0x48, arg5 + 0xC);
    func_800330A4((void *) arg5);
    func_80026DEC((void *) arg5, (void *) (arg5 + 0xC), (void *) (arg5 + 0x18));
    func_800330A4((void *) (arg5 + 0x18));
    func_80026DEC((void *) (arg5 + 0x18), (void *) arg5, (void *) (arg5 + 0xC));
}
