#include "common.h"

extern void func_8003EF44(s32 *);
extern void func_8003F8F0(s32 *);
extern void func_8003F900(s32 *);
extern void func_8003F45C(s32 *);
extern void func_8003F8F8(s32 *);

void func_800143BC(s32 *p) {
    switch (*p) {
    case 1:
    case 2:
        func_8003EF44(p);
        break;
    case 4:
        func_8003F8F0(p);
        break;
    case 6:
        func_8003F900(p);
        break;
    case 3:
        func_8003F45C(p);
        break;
    case 5:
        func_8003F8F8(p);
        break;
    }
}
