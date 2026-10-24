#include "common.h"

extern void func_8003EF44(void);
extern void func_8003F8F0(void);
extern void func_8003F900(void);
extern void func_8003F45C(void);
extern void func_8003F8F8(void);

void func_800143BC(s32 *p) {
    switch (*p) {
    case 1:
    case 2:
        func_8003EF44();
        break;
    case 4:
        func_8003F8F0();
        break;
    case 6:
        func_8003F900();
        break;
    case 3:
        func_8003F45C();
        break;
    case 5:
        func_8003F8F8();
        break;
    }
}
