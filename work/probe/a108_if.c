#include "common.h"

extern s32 D_8008ADFC;
extern u16 D_8008AE08;
extern u8 D_8008AE00[8];

s32 func_80012078(s32);
void func_80014450(void *);
void func_80014464(void *, void *);
void func_8001C488(s32, s32, void *, void *);
void func_8001A9DC(void);

s32 func_8001A108(s32 arg0) {
    s32 i;
    u8 *slot;
    u8 *p;
    s32 n;

    i = D_8008ADFC;
    if (i > 0) {
        return 0;
    }
    slot = D_8008AE00 + i * 8;
    p = (u8 *)func_80012078(3);
    if (p == NULL) {
        return 0;
    }
    func_80014450(p);
    *(u16 *)(slot + 4) = D_8008AE08 + D_8008ADFC * 6;
    func_80014464(p, slot);
    *(u8 **)slot = p;
    if (arg0 == 1) {
        n = 3;
    } else if (arg0 == 0) {
        n = 2;
    } else if (arg0 == 2) {
        n = 4;
    } else {
        goto done;
    }
    func_8001C488(n, 0xFFFF, p, func_8001A9DC);
done:
    D_8008ADFC = D_8008ADFC + 1;
    return (s32)p;
}
