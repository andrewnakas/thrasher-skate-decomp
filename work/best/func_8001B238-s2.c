#include "common.h"

extern s32 D_8008A088;
extern u8 *D_8008ADB8;
extern u32 D_8008ADBC;
extern u8 D_8008C45C[];
extern u8 D_6040[];
extern u8 D_16A8[];
extern u8 D_8008A08C[];
extern u8 D_8008A098[];
extern u8 D_8008A0A4[];
extern u8 D_8008A0B0[];
extern u8 D_8008B4F8[];
extern u8 D_8008AC28[];
extern u8 D_800B9390[];

static const u32 D_80010668 = 0x8008B4F4;
static const u32 D_8001066C = 0x800B7D38;

extern s32 func_8001B1CC(s32, s32);
extern void func_8005737C(void *);
extern void *memset(void *, s32, u32);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void FlushCache(void);

s32 func_8001B238(s32 mode) {
    u32 want;
    u32 have;

    if (D_8008A088 == 0xFFFF) {
        D_8008ADB8 = D_8008C45C;
        D_8008ADBC = (u32) D_6040;
        if ((u32) D_6040 < (u32) D_16A8) {
            D_8008ADBC = (u32) D_16A8;
        }
    }
    switch (mode) {
    case 0:
        if (D_8008A088 == 0) {
            return 0;
        }
        memset(D_8008ADB8, 0, D_8008ADBC);
        D_8008A088 = 0;
        func_8001B1CC((s32) D_8008A08C, (s32) D_8001066C);
        func_8001B1CC((s32) D_8008A098, (s32) D_80010668);
        EnterCriticalSection();
        FlushCache();
        ExitCriticalSection();
        want = (u32) D_800B9390;
        have = *(u32 *) D_8008B4F8;
        break;
    case 1:
        if (mode == D_8008A088) {
            return 0;
        }
        D_8008A088 = mode;
        memset(D_8008ADB8, 0, D_8008ADBC);
        func_8001B1CC((s32) D_8008A0A4, (s32) D_8001066C);
        func_8001B1CC((s32) D_8008A0B0, (s32) D_80010668);
        EnterCriticalSection();
        FlushCache();
        ExitCriticalSection();
        want = (u32) func_8005737C;
        have = *(u32 *) D_8008AC28;
        break;
    default:
        return 1;
    }
    return have != want;
}
