#include "common.h"

extern s32 D_8008AFF0;
extern s32 D_8008B010;
extern s32 D_8008B014;
extern u8 D_8008AF84[8];
extern u8 D_8008AF94[8];
extern s16 D_8008AF86;
extern s16 D_8008AF8A;
extern s16 D_8008AF8E;
extern u8 D_800A4F00[];

extern void func_8002A0F8(void *p);
extern s32 func_8003B848(void);
extern void func_8003B754(s32 a, s32 *out);
extern void func_8002A044(void *p);
extern void func_80011F24(void *a, void *b);
extern void func_8002BD64(void *p, s16 *t);

void func_80027630(void) {
    s16 t[3];
    s32 v;
    s32 h;

    if (D_8008AFF0 != 0) {
        D_8008AFF0 = 0;
        func_8002A0F8(D_800A4F00);
    }
    h = func_8003B848();
    func_8003B754(0, &v);
    if (D_8008B010 != h || D_8008B014 != v) {
        D_8008B010 = h;
        D_8008B014 = v;
        func_8002A044(D_800A4F00);
    }
    func_80011F24(D_8008AF84, D_8008AF94);
    {
        s32 x = D_8008AF86;
        s32 y = D_8008AF8A;
        s32 z = D_8008AF8E;
        t[0] = x;
        t[1] = y;
        t[2] = z;
    }
    func_8002BD64(D_800A4F00, t);
}
