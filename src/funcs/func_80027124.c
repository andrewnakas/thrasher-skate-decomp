#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} V_80027124;

extern u8 *func_80022118(void);
extern void func_80022148(u8 *e, V_80027124 *v);
extern void func_8002221C(u8 *e, s32 a, s32 b, s32 c);

u8 *func_80027124(void) {
    u8 *e;
    V_80027124 v;

    e = func_80022118();
    if (e != 0) {
    v.f0 = 2;
    v.f10 = 0x1999;
    v.f14 = 0xCCCC;
    v.f18 = 0x6666;
    v.f4 = 0x1E0000;
    v.f8 = 0;
    v.fC = 0;
    func_80022148(e, &v);
    v.f4 = 0xFFE20000;
    v.f8 = 0;
    v.fC = 0xFFF60000;
    func_80022148(e, &v);
    v.f4 = 0xFFE20000;
    v.f8 = 0;
    v.fC = 0x000A0000;
    func_80022148(e, &v);
    func_8002221C(e, 0, 1, 0x100000);
    func_8002221C(e, 0, 2, 0x100000);
    func_8002221C(e, 1, 2, 0x100000);
    }
    return e;
}
