#include "common.h"

extern s32 D_8008AFF0;
extern s32 D_8008B010;
extern s32 D_8008B014;
extern u8 D_800A4F00[];
extern u8 D_8008AF84;
extern u8 D_8008AF94;
extern s16 D_8008AF86;
extern s16 D_8008AF8A;
extern s16 D_8008AF8E;
extern void func_8002A0F8(u8 *);
extern s32 func_8003B848(void);
extern void func_8003B754(s32, s32 *);
extern void func_8002A044(u8 *);
extern void func_80011F24(u8 *, u8 *);
extern s32 func_8002BD64(u8 *, s16 *);

s32 func_80027630(void) {
    s16 arr[3];
    s32 t;
    s32 h;
    s32 a;
    s32 b;
    s32 c;

    if (D_8008AFF0 != 0) {
        D_8008AFF0 = 0;
        func_8002A0F8(D_800A4F00);
    }
    h = func_8003B848();
    func_8003B754(0, &t);
    if (D_8008B010 != h || D_8008B014 != t) {
        D_8008B010 = h;
        D_8008B014 = t;
        func_8002A044(D_800A4F00);
    }
    func_80011F24(&D_8008AF84, &D_8008AF94);
    a = D_8008AF86;
    b = D_8008AF8A;
    c = D_8008AF8E;
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    return func_8002BD64(D_800A4F00, arr);
}
