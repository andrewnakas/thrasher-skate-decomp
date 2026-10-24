#include "common.h"

extern u8 D_8006E750[];
extern u8 *func_80034CF0(s32);
extern void func_80037A5C(u8 *, s32);
extern s32 func_8001B40C(u8 *, s32);
extern void func_8001B504(void);
extern s32 func_8001D88C(void);
extern s32 func_8001C27C(void);
extern void func_80037A80(void);
extern void func_80034D30(u8 *);

s32 func_8001A1EC(void) {
    u8 *p;

    p = func_80034CF0(0x4000);
    func_80037A5C(p, 0x4000);
    if (func_8001B40C(D_8006E750, 1)) {
        return 1;
    }
    func_8001B504();
    if (func_8001D88C()) {
        return 1;
    }
    if (func_8001C27C()) {
        return 1;
    }
    func_80037A80();
    func_80034D30(p);
    return 0;
}
