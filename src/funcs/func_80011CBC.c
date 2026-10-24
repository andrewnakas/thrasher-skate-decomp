#include "common.h"
typedef struct { s32 x, y, z; } Vec3;
extern Vec3 D_80089F34;
extern s32 D_8008AC9C;
extern void *D_8008ACA0;
extern u8 D_8009249C[];
void func_80011D34(s16);
void func_80011D60(Vec3 *, Vec3 *);
void *memset(void *, s32, u32);
s32 func_80011CBC(void) {
    Vec3 a;
    Vec3 b;
    D_8008AC9C = 0;
    D_8008ACA0 = D_8009249C;
    func_80011D34(0x271C);
    a = D_80089F34;
    memset(&b, 0, sizeof(b));
    func_80011D60(&a, &b);
    return 0;
}
