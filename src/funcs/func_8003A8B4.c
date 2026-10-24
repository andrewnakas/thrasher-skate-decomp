#include "common.h"

extern s32 D_8008242C[];
extern s32 D_8008A710;
extern s32 D_8008A6EC;
extern void func_80059408(void);
extern void func_80059AB0(s32 a);
extern void func_80059C24(s32 a);
extern void func_80059CF0(s32 a);
extern void SetVideoMode(s32 a);
extern void InitGeom(void);
extern void func_8003AECC(void);
extern void func_80045838(void);
extern void func_80059498(void (*f)(void));
extern void func_8003A94C(void);
extern void func_8003ADBC(s32 a, s32 b, s32 c, s32 d);
extern void func_80033EB4(void);
extern void func_8003B418(s32 a);

void func_8003A8B4(void) {
    func_80059408();
    func_80059AB0(0);
    func_80059C24(0);
    func_80059CF0(0);
    SetVideoMode(0);
    InitGeom();
    func_8003AECC();
    func_80045838();
    func_80059498(func_8003A94C);
    func_8003ADBC(0, 0, 0, 1);
    func_80033EB4();
    D_8008242C[0] = 1;
    D_8008A710 = 0;
    func_8003B418(0);
    D_8008A6EC = 0;
}
