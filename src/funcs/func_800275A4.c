#include "common.h"

extern u8 D_800A4F00[];
extern u8 D_8009CE50[];

extern s32 D_8008AFF0;
extern s32 D_8008AFD4;
extern s32 D_8008AFD8;
extern s32 D_8008AFEC;
extern s32 D_8008AFE8;
extern s32 D_8008AFE4;
extern s32 D_8008AFE0;
extern s32 D_8008AFDC;
extern s32 D_8008B084;
extern s32 D_8008AFA8;
extern s32 D_8008B010;
extern s32 D_8008B014;

extern void func_8002B168(void);
extern void func_8002E8B0(void);
extern void func_8002DC70(void);

s32 func_800275A4(void) {
    memset(D_800A4F00, 0, 0x60);
    memset(D_8009CE50, 0, 0x4E00);
    D_8008AFF0 = 1;
    D_8008AFD4 = 0;
    D_8008AFD8 = 0;
    D_8008AFEC = 0;
    D_8008AFE8 = 0;
    D_8008AFE4 = 0;
    D_8008AFE0 = 0;
    D_8008AFDC = 0;
    D_8008B084 = 0;
    D_8008AFA8 = 0;
    D_8008B010 = 0;
    D_8008B014 = 0;
    func_8002B168();
    func_8002E8B0();
    func_8002DC70();
    return 0;
}
