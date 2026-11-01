#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s32 flags;
    u8 pad14[0x158 - 0x14];
    s16 unk158;
    s16 unk15A;
    u8 pad15C[0x2E4 - 0x15C];
} Plr558A8;

extern void func_800309C4(s32, s32, s32, s32, s32);
extern void func_800BA31C(s32);
extern void func_800BA534(s32, s32);
extern void func_800BA778(s32, s32);
extern void func_800BABFC(void);
extern s32 func_800C5774(void);
extern s32 func_800C6EF0(void);
extern void func_800C7414(s32, s32);
extern void func_800C8128(void);
extern void func_800CFBBC(void);
extern void func_800D2230(u32);
extern void func_800D2278(u32);
extern void func_800D3750(void);
extern void func_800DCEC4(s32, s32);
extern s32 func_800DD530(s32);

extern u8 D_8008AB17;
extern s8 D_8008B4A5;
extern u8 D_8008B4A7;
extern u8 D_8008B4A8;
extern s32 D_8008B4AC;
extern s8 D_8008B4C0;
extern u8 D_8008B4E0[8];
#define D_8008B4D8 (&D_8008B4E0[-8])
#define D_8008B4DC (&D_8008B4E0[-4])
extern Plr558A8 D_8008C7F4[];

u8 func_800558A8(u32 mode) {
    Plr558A8 *p;
    u32 i;
    u8 sel;
    s32 src;
    s16 hundred;
    s32 eight;

    if (D_8008AB17 != mode) {
        D_8008B4C0 = -1;
        D_8008B4AC = 0;
        switch (D_8008AB17) {
        case 0:
            if (D_8008B4D8[0] != 0) {
                func_800DCEC4(D_8008B4A7, 0);
            }
            if (mode != 1) {
                for (i = 0; i < 9; i++) {
                    func_800D2278(i);
                }
            }
            break;
        case 1:
            break;
        case 2:
        case 5:
            sel = func_800C6EF0();
            func_800DCEC4(sel, 0);
            func_800C7414(func_800DD530(sel), 0);
            if (func_800C5774() == 3) {
                func_800C7414(D_8008B4DC[0], 1);
            }
            func_800BA534(D_8008B4DC[0], 5);
            func_800BA31C(D_8008B4DC[0]);
        case 4:
            switch (D_8008AB17) {
            case 5:
                func_800CFBBC();
            case 2:
                if (func_800C5774() == 0) {
                    func_800D2278(9);
                    func_800D2278(10);
                }
                break;
            case 4:
                func_800D2278(11);
                break;
            }
            if (func_800C5774() == 0) {
                func_800309C4(0x3E9, 6, 0, 0, 0);
            }
            break;
        case 3:
            func_800DCEC4(D_8008B4A7, 0);
            func_800BA534(D_8008B4DC[0], 0);
            break;
        }
        switch (mode) {
        case 0:
            for (i = 0; i < 9; i++) {
                func_800D2230(i);
            }
            break;
        case 1:
            break;
        case 2:
        case 5:
            if (func_800C5774() != 0) {
                for (i = 0; i < D_8008B4D8[0]; i++) {
                    func_800C7414(i, 0);
                    D_8008C7F4[i].unk15A = 0;
                    D_8008C7F4[i].unk158 = 100;
                }
            }
            func_800C8128();
        case 4:
            if (mode == 4) {
                src = D_8008B4A8;
            } else {
                src = func_800C6EF0();
            }
            for (i = 0; i < D_8008B4D8[0]; i++) {
                if (i == D_8008B4DC[0] || func_800C5774() == 8) {
                    D_8008C7F4[i].flags &= ~1;
                }
            }
            sel = src;
            func_800C7414(func_800DD530(sel), 1);
            func_800BA31C(func_800DD530(sel));
            func_800DCEC4(sel, 2);
            func_800BA534(func_800DD530(sel), 1);
            if (mode != 4) {
                func_800BA778(func_800DD530(sel), 0);
            }
            switch (mode) {
            case 2:
                if (func_800C5774() == 0) {
                    func_800D2230(9);
                    func_800D2278(10);
                }
                break;
            case 4:
                for (i = 0; i < 12; i++) {
                    func_800D2278(i);
                }
                func_800D2230(11);
                break;
            case 5:
                func_800D2230(10);
                func_800D2230(9);
                break;
            default:
                func_800BABFC();
                func_800D3750();
                break;
            }
            if (func_800C5774() == 0) {
                func_800309C4(0x3E9, 2, 0, 0, 0);
            }
            break;
        case 3:
            sel = D_8008B4A7;
            func_800DCEC4(sel, 2);
            func_800BA534(func_800DD530(sel), 1);
            func_800BA778(func_800DD530(sel), 1);
            break;
        }
        D_8008AB17 = mode;
        D_8008B4A5 = 0;
    }
    return D_8008AB17;
}
