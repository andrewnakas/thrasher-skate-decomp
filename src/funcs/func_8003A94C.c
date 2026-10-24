#include "common.h"

extern s32 D_8008A6DC;
extern volatile s32 D_8008A71C;
extern volatile s32 D_8008A720;
extern s32 D_8008B204;
extern s32 D_8008A6EC;
extern void func_80063204(void);
extern void func_8003A448(void);
extern void func_800357F0(void);
extern void func_8003AA14(void);

void func_8003A94C(void) {
    if (D_8008A6DC == 1) {
        func_80063204();
    }
    D_8008A71C--;
    if (D_8008A71C <= 0) {
        func_8003A448();
        D_8008A71C = 2;
    }
    D_8008A720--;
    if (D_8008A720 == 0) {
        func_800357F0();
    }
    if (D_8008B204 != 0) {
        func_8003AA14();
    }
    D_8008A6EC++;
}
