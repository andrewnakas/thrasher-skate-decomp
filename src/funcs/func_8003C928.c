#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u8 pad4[4];
    s32 flags;
    u8 padC[8];
    s32 f14;
    s32 f18;
    u8 pad1C[0x10];
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
} Spad_3C928;

typedef struct {
    u8 pad0[0x138];
    s16 unk138;
    u8 pad13A[6];
    s32 unk140;
    s32 unk144;
    u8 pad148[8];
    s32 unk150;
    s32 unk154;
} Cam_3C928;

#define SPAD ((Spad_3C928 *) 0x1F800000)

void func_80027630();
void *func_80034C20(s32);
void func_8003D318(void);
s32 func_8003E410(s32);
void func_8003ED04();
extern Cam_3C928 D_8008234C;
extern s32 D_8008A770;
extern s32 D_8008B088[2];
#define D_8008B084 (D_8008B088[-1])
extern s32 D_8008B238[2];
#define D_8008B234 (D_8008B238[-1])
extern s32 D_8008B240[2];
#define D_8008B23C (D_8008B240[-1])
extern u8 *D_8008B308;
extern s32 D_8008B30C;
extern s32 D_8008B310;
extern s32 D_8008B314;
extern s32 D_8008B318;
extern s32 *D_8008B31C;
extern s32 *D_8008B320;
extern s32 *D_8008B324;
extern s32 D_8008B334[2];
#define D_8008B32C (D_8008B334[-2])
#define D_8008B330 (D_8008B334[-1])
extern s32 D_8008B3B0[2];
#define D_8008B3AC (D_8008B3B0[-1])
extern s32 D_800A4F00[];

void func_8003C928(void) {
    Spad_3C928 *sp = SPAD;

    if (D_8008A770 != 0) {
        D_8008A770 = 0;
        D_8008B320 = func_80034C20(D_8008B084 * 0xC);
        D_8008B31C = func_80034C20(0x204);
        D_8008B308 = (u8 *) D_8008B31C + 0x204;
    }
    sp->flags = D_800A4F00[0];
    if (!(D_800A4F00[0] & 1)) {
        D_8008B30C = D_8008B234;
        D_8008B310 = D_8008B234 > 0x7FFF ? 0x7FFF : D_8008B234;
        D_8008B318 = D_8008B310 + 0x2C6 > 0x7FFF ? 0x7FFF : D_8008B310 + 0x2C6;
        D_8008B314 = -0x266;
    } else {
        D_8008B30C = D_8008B23C;
        D_8008B310 = D_8008B23C + 0x190 > 0x7FFF ? 0x7FFF : D_8008B23C + 0x190;
        D_8008B318 = D_8008B310 + 0x2C6 > 0x7FFF ? 0x7FFF : D_8008B310 + 0x2C6;
        D_8008B314 = -0x266;
    }
    D_8008B324 = D_8008B31C;
    func_8003ED04();
    sp->f14 = D_8008B330;
    sp->f18 = D_8008B32C;
    sp->y = D_8008B310;
    sp->x = D_8008B30C;
    sp->f2C = D_8008234C.unk140;
    sp->f30 = D_8008234C.unk144;
    sp->f34 = D_8008234C.unk150;
    sp->f38 = D_8008234C.unk154;
    sp->f3C = D_8008234C.unk138 >> 1;
    D_8008B324 = D_8008B31C;
    func_80027630();
    *D_8008B324 = 0;
    func_8003D318();
    D_8008B330 = sp->f14;
    D_8008B32C = sp->f18;
    D_8008B3AC = func_8003E410(D_8008B3AC);
}
