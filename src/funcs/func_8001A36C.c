#include "common.h"

extern s32 D_8008ADD4;
extern u16 D_8008ADF8;
extern s32 D_8008ADD8;

void *func_80012078(s32);
void func_80014464(void *, void *, s32);
void func_80034D4C(void *, void *, s32);
void func_8001C488(s32, s32, void *, void *);
void func_8001A9DC(void);

void *func_8001A36C(void *arg0) {
    u8 *slot;
    void *p;

    if (D_8008ADD4 < 2) {
        slot = (u8 *)&D_8008ADD8 + D_8008ADD4 * 16;
        p = func_80012078(1);
        if (p == 0) {
            return 0;
        }
        *(u16 *)(slot + 0xC) = D_8008ADF8 + D_8008ADD4 * 3;
        func_80014464(p, slot, D_8008ADD4);
        func_80034D4C(slot + 4, arg0, 8);
        *(void **)slot = p;
        func_8001C488(1, 0xFFFF, p, func_8001A9DC);
        D_8008ADD4 = D_8008ADD4 + 1;
        return p;
    }
    return 0;
}
