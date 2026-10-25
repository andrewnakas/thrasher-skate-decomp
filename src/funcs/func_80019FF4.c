#include "common.h"

extern s32 D_8008ADC8;
extern s32 D_8008ADCC;
extern s32 D_8008ADD4;
extern s32 D_8008ADFC;
extern s32 D_8008AE0C;

extern void func_8001B3A0(void);
extern s32 func_8001C174(void);
extern void func_800275A4(void);
extern void func_8001B4E4(void);
extern void func_8001A548(void);
extern void func_8001D6D8(s32, s32);
extern void func_8001B3B0(void);

s32 func_80019FF4(void) {
    func_8001B3A0();
    if (func_8001C174()) {
        return 1;
    }
    func_800275A4();
    D_8008ADC8 = 1;
    D_8008ADCC = 0;
    D_8008ADD4 = 0;
    D_8008ADFC = 0;
    D_8008AE0C = 0;
    D_8008ADFC = 0;
    func_8001B4E4();
    func_8001A548();
    func_8001D6D8(0x30, 0x40);
    func_8001B3B0();
    return 0;
}
