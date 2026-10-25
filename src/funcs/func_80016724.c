#include "common.h"

extern u8 D_80089F9C;
extern s32 D_80089FA0;
extern u8 D_80089FA4;
extern s32 D_80089FA8;

void func_800584F4(void);
void func_80055820(void);
void func_800379F4(void);
void func_80011FFC(void);
void func_8003AF0C(void);
void func_800464B0(void);
void func_80034BD8(s32);
void *func_80034C14(void);
s32 func_80034C7C(void);
void func_8003AF4C(s32, s32);
void func_80011F84(void);
s32 func_80057FC4(void);
s32 func_8005458C(void);
void func_80046478(void);

s32 func_80016724(void) {
    void *p;
    s32 s;

    switch (D_80089F9C) {
    case 0:
        break;
    case 1:
        func_800584F4();
        func_800379F4();
        func_80011FFC();
        func_8003AF0C();
        func_800464B0();
        break;
    case 2:
        func_80055820();
        func_800379F4();
        func_80011FFC();
        func_8003AF0C();
        func_800464B0();
        break;
    }
    if (D_80089FA8 != 0) {
        func_80034BD8(D_80089FA8);
        p = func_80034C14();
        memset(p, 0xFF, func_80034C7C());
        D_80089FA8 = 0;
    }
    D_80089F9C = 0;
    D_80089FA8 = func_80034C14();
    s = D_80089FA4;
    switch (s) {
    case 0:
        break;
    case 1:
        func_8003AF4C(1, 0);
        func_80011F84();
        if (func_80057FC4() != 0) {
            return 1;
        }
        D_80089F9C = s;
        func_80046478();
        func_8003AF4C(1, 1);
        break;
    case 2:
        func_80011F84();
        func_8003AF4C(0, 0);
        if (func_8005458C() != 0) {
            return 1;
        }
        func_80046478();
        D_80089F9C = s;
        func_8003AF4C(0, 1);
        break;
    }
    D_80089FA4 = 0;
    D_80089FA0 = 0;
    return 0;
}
