#include "common.h"

typedef struct {
    u8 pad0[0x54];
    u8 f54;
    u8 f55;
    u8 f56;
    u8 f57;
    u8 pad58[0x5B - 0x58];
    u8 f5B;
    u8 pad5C[0x65 - 0x5C];
    u8 f65;
    u8 f66;
    u8 pad67;
    u8 f68;
    u8 pad69[0x70 - 0x69];
} Rec_80057FC4;

extern void func_80019FF4(void);
extern void func_8001B1AC();
extern void func_8001B238(s32);
extern s32 func_8001BED4(s32);
extern void func_8001BF2C(s32);
extern void func_8001BFA8(s32);
extern void func_800309C4(s32, s32, s32, s32, s32);
extern void func_80056D20(void);
extern void func_80057200();
extern void func_8005722C(void);
extern void func_8005737C(void);
extern s32 func_80058448(s32);
extern s32 func_800BB314(void);
extern s32 func_800BB338(void);
extern void func_800BD87C(s32);
extern void func_800C2020(s32);
extern void func_800C5208(s32);
extern void func_800CBB64(s32);
extern void func_800CE214(s32);
extern void func_800CF200(s32);
extern void func_800D211C(s32);
extern void func_800D2260(s32);
extern void func_800D269C(s32);
/* Absolute lui/%lo globals spelled as symbol-minus-offset of a small (8-byte) extern:
   maspsx never makes sym-N gp-relative, so the assembler expands them like the game. */
extern s32 D_8008ABE0[2];
extern s32 D_8008B4E0[2];
#define D_8008AB28 (D_8008ABE0[-46])
#define D_8008AB2C (D_8008ABE0[-45])
#define D_8008AB30 (D_8008ABE0[-44])
#define D_8008AB34 (D_8008ABE0[-43])
#define D_8008AB38 (D_8008ABE0[-42])
#define D_8008AB3C (D_8008ABE0[-41])
#define D_8008AB40 (D_8008ABE0[-40])
#define D_8008AB44 (D_8008ABE0[-39])
#define D_8008AB48 (D_8008ABE0[-38])
#define D_8008AB68 (D_8008ABE0[-30])
#define D_8008AB6C (D_8008ABE0[-29])
#define D_8008AB70 (D_8008ABE0[-28])
#define D_8008AB74 (D_8008ABE0[-27])
#define D_8008AB78 (D_8008ABE0[-26])
#define D_8008AB7C (((u8 *) D_8008ABE0)[-0x64])
#define D_8008B4DC (((u8 *) D_8008B4E0)[-4])
extern s32 D_8008B4E8;
extern s32 D_8008B4EC;
extern Rec_80057FC4 D_800B2428[];

s32 func_80057FC4(void) {
    s32 r;

    r = 0;
    switch (D_800B2428[D_8008B4DC].f65) {
    case 0:
        if (D_8008AB68 != 0) {
            r = func_8001BED4(6);
            D_8008AB68 = 0;
        }
        break;
    case 1:
        if (D_8008AB6C != 0) {
            r = func_8001BED4(2);
            D_8008AB6C = 0;
        }
        break;
    case 4:
        if (D_8008AB70 != 0) {
            r = func_8001BED4(3);
            D_8008AB70 = 0;
        }
        break;
    case 7:
        if (D_8008AB74 != 0) {
            r = func_8001BED4(4);
            D_8008AB74 = 0;
        }
        break;
    case 10:
        if (D_8008AB78 != 0) {
            r = func_8001BED4(5);
            D_8008AB78 = 0;
        }
        break;
    }
    if (D_8008AB48 != 0) {
        r = func_8001BED4(7);
    }
    if (r == 0) {
        func_8001B1AC();
    }
    func_8001B238(0);
    if (func_800BB314() != 0) {
        return 1;
    }
    func_8005737C();
    D_8008B4E8 = 0;
    D_8008B4EC = 0;
    func_80019FF4();
    func_8001BF2C(0);
    func_8001BFA8(0);
    if (func_80058448(0) != 0) {
        return 1;
    }
    if (func_800BB338() != 0) {
        return 1;
    }
    if (D_8008AB28 != 0) {
        func_80057200();
        func_80056D20();
        func_8005722C();
        D_8008AB28 = 0;
    }
    func_800309C4(1000, 1, 0, 0, 0);
    if (D_800B2428[D_8008B4DC].f65 > D_8008AB7C) {
        D_8008AB34 = 1;
    } else {
        D_8008AB34 = 0;
    }
    if (D_8008AB2C != 0) {
        func_800D211C(0);
        D_8008AB2C = 0;
        return 0;
    }
    if (D_800B2428[D_8008B4DC].f66 == 0) {
        func_800BD87C(0);
        D_8008AB30 = 0;
        return 0;
    }
    if (D_8008AB40 != 0 && D_8008AB44 != 0) {
        func_800D269C(2);
        D_8008AB40 = 0;
        D_8008AB44 = 0;
        return 0;
    }
    if (D_8008AB48 != 0) {
        func_800D2260(2);
        D_8008AB48 = 0;
        return 0;
    }
    if (D_800B2428[D_8008B4DC].f68 != 0) {
        func_800CE214(2);
        return 0;
    }
    if (D_800B2428[D_8008B4DC].f5B != 0) {
        func_800CBB64(1);
        return 0;
    }
    if (D_8008AB38 != 0) {
        func_800CF200(0);
        D_8008AB38 = 0;
        return 0;
    }
    if (D_800B2428[D_8008B4DC].f55 != 0 || D_800B2428[D_8008B4DC].f56 != 0 || D_800B2428[D_8008B4DC].f54 != 0 || D_800B2428[D_8008B4DC].f57 != 0) {
        D_8008AB30 = 0;
        func_800C5208(2);
        return 0;
    }
    if (D_8008AB3C == 0 && D_8008AB34 != 0) {
        func_800C2020(2);
        D_8008AB34 = 0;
        return 0;
    }
    func_800C2020(1);
    return 0;
}
