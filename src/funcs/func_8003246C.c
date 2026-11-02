#include "common.h"

extern s32 D_800B9390[1];
extern s32 D_800D42AC[1];

/* D_800D42AC / D_800DF16C reached by assembler la macros: spelled as offsets from a neighbour >= 0x8000 below (a nearer one is gp-relative) */
#define HEAP_LO ((u8 *) &D_800B9390[0x6BC7])
#define HEAP_MIN ((u8 *) &D_800D42AC[0x2BB0])
extern u8 *D_800843EC[1];
extern s32 D_80089FB0[1];
extern s32 D_8008A41C;
extern char D_8008A420[];

void func_8005D258(void);
void SetMem(s32);
void func_80059408(void);
void func_80034B98(void);
void func_80036094(void);
void func_80037D10(void);
void func_80034DE8(void);
void func_80059C24(s32);
void func_8003A8B4(void);
void func_800168C4(void);
void func_8003B8F8(void);
void func_8001BED4(s32);
void func_80032A9C(s32);
void func_8003A404(void);
void func_80016654(void);
void func_8003A428(void);
void func_800350C8(void);
s32 func_80016698(void);
void func_80059D88(s32);
s32 VSync(s32);
void func_80035860(void);
void func_8003AF0C(void);
void func_8003A468(void);
void func_80037D50(void);
void func_800168E4(void);
void func_80034EF4(void);
void func_80036120(void);
void func_80059498(s32);
void func_80059C90(s32);
void func_8005C964(s32);
void func_8005CBD8(s32);
void func_8005CBC4(s32);
s32 CdInit(void);
void func_800594FC(void);
void func_80059AB0(s32);
s32 printf(const char *, ...);
extern void exit(s32) __attribute__((noreturn));

void func_8003246C(void) {
    u8 *p;

    func_8005D258();
    p = HEAP_LO;
    if (p < HEAP_MIN) {
        p = HEAP_MIN;
    }
    D_800843EC[-1] = p;
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
    while (D_80089FB0[-1] == 0) {
        if (D_8008A41C == 0) {
            func_8003A428();
        }
        func_800350C8();
        if (func_80016698() != 0) {
            D_80089FB0[-1] = 1;
        }
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
