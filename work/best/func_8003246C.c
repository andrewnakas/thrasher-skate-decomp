#include "common.h"

extern s32 func_8005D258(void);
extern s32 SetMem(s32);
extern s32 func_80059408(void);
extern s32 func_80034B98(void);
extern s32 func_80036094(void);
extern s32 func_80037D10(void);
extern s32 func_80034DE8(void);
extern s32 func_80059C24(s32);
extern s32 func_8003A8B4(void);
extern s32 func_800168C4(void);
extern s32 func_8003B8F8(void);
extern s32 func_8001BED4(s32);
extern s32 func_80032A9C(s32);
extern s32 func_8003A404(void);
extern s32 func_80016654(void);
extern s32 func_8003A428(void);
extern s32 func_800350C8(void);
extern s32 func_80016698(void);
extern s32 func_80059D88(s32);
extern s32 VSync(s32);
extern s32 func_80035860(void);
extern s32 func_8003AF0C(void);
extern s32 func_8003A468(void);
extern s32 func_80037D50(void);
extern s32 func_800168E4(void);
extern s32 func_80034EF4(void);
extern s32 func_80036120(void);
extern s32 func_80059498(s32);
extern s32 func_80059C90(s32);
extern s32 func_8005C964(s32);
extern s32 func_8005CBD8(s32);
extern s32 func_8005CBC4(s32);
extern s32 CdInit(void);
extern s32 func_800594FC(void);
extern s32 func_80059AB0(s32);
extern s32 printf(char *, ...);
extern void exit(s32);

typedef struct Big_8003246C {
    s32 unk0;
    u8 pad4[0x3C];
} Big_8003246C;

extern Big_8003246C D_800843E8;
extern Big_8003246C D_80089FAC;
extern u8 D_800D42AC[];
extern u8 D_800DF16C[];
extern char D_8008A420[];
extern s32 D_8008A41C;

void func_8003246C(void) {
    u8 *top;

    func_8005D258();
    top = D_800D42AC;
    if ((u32) top < (u32) D_800DF16C) {
        top = D_800DF16C;
    }
    D_800843E8.unk0 = (s32) top;

    SetMem(2);
    func_80059408();
    func_80034B98();
    func_80036094();
    func_80037D10();
    func_80034DE8();
    func_80059C24(0);
    func_8003A8B4();
    func_800168C4();
    func_8003B8F8();
    func_8001BED4(8);
    func_8001BED4(0);
    func_80032A9C(0);

    if (D_8008A41C == 0) {
        func_8003A404();
    }
    func_80016654();

    if (D_80089FAC.unk0 == 0) {
        do {
            if (D_8008A41C == 0) {
                func_8003A428();
            }
            func_800350C8();
            if (func_80016698() != 0) {
                D_80089FAC.unk0 = 1;
            }
        } while (D_80089FAC.unk0 == 0);
    }

    func_80059D88(0);
    VSync(0);
    VSync(3);
    func_80035860();
    func_8003AF0C();

    if (D_8008A41C == 0) {
        func_8003A468();
    }

    func_80037D50();
    func_800168E4();
    func_80034EF4();
    func_80036120();
    func_80059498(0);
    func_80059C90(0);
    func_8005C964(0);
    func_8005CBD8(0);
    func_8005CBC4(0);
    CdInit();
    func_800594FC();
    func_80059AB0(3);

    printf(D_8008A420);
    exit(0);
}
